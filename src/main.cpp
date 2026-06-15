#include "debugger.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include "../include/emu.hpp"
#include "../include/instructions.hpp"
#include "../include/apu.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <array>
#include <optional>

#include "ppu.hpp"
#include "apu.hpp"
#include "../fonts/ttf/JetBrainsMono-Medium.h"

class SoundStream : public sf::SoundStream {
private:
    AudioRingBuffer& ringBuffer;
    std::vector<int16_t> tempBuffer;

public:
    SoundStream(AudioRingBuffer& buffer) : ringBuffer(buffer) {
		initialize(1, 44100, { sf::SoundChannel::Mono });
        tempBuffer.resize(4096);
    }

protected:
    bool onGetData(Chunk& data) override {
        size_t count = 0;
        int16_t sample;

        while (count < 512) {
            if (ringBuffer.pop(sample)) {
                tempBuffer[count++] = sample;
            }
            else {
                break;
            }
        }

        if (count == 0) {
            tempBuffer[0] = 0;
            count = 1;
        }

        data.samples = tempBuffer.data();
        data.sampleCount = count;
        return true;
    }

    void onSeek(sf::Time timeOffset) override {}
};

int main(int argc, char* argv[]) {
    bool headless = false;
    std::string inputRom = "C:\\Pratyush\\study\\GB-emulator\\roms\\tests\\cpu_instrs\\individual\\02-interrupts.gb";
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--headless") {
            headless = true;
        } else {
            inputRom = arg;
        }
    }

    if (headless) {
        init_instructions();
        Emulator emu(inputRom);
        std::cout << "Running headlessly: " << inputRom << std::endl;
        uint64_t updates = 0;
        constexpr uint64_t MAX_UPDATES = 100000000;

        const auto& mmu = emu.getDebugContext().mmu.get();
        size_t last_printed_len = 0;

        while (emu.is_running() && updates < MAX_UPDATES) {
            if (updates == 0) {
                std::cout << "RAM at 0xA000: " << (int)mmu.read_data(0xA000)
                          << " 0xA001: " << (int)mmu.read_data(0xA001)
                          << " 0xA002: " << (int)mmu.read_data(0xA002)
                          << " 0xA003: " << (int)mmu.read_data(0xA003) << std::endl;
            }
            emu.run_one();
            updates++;

            if (mmu.read_data(0xA001) == 0xDE &&
                mmu.read_data(0xA002) == 0xB0 &&
                mmu.read_data(0xA003) == 0x61) {
                
                uint16_t text_addr = 0xA004;
                std::string current_text = "";
                while (true) {
                    char c = mmu.read_data(text_addr);
                    if (c == 0) break;
                    current_text += c;
                    text_addr++;
                }
                if (current_text.length() > last_printed_len) {
                    std::cout << current_text.substr(last_printed_len) << std::flush;
                    last_printed_len = current_text.length();
                }

                uint8_t status = mmu.read_data(0xA000);
                if (status != 0x80) {
                    const auto& regs = emu.getDebugContext().regs.get();
                    std::cout << "\nTest finished with status: " << (int)status 
                              << " after " << updates << " instructions." 
                              << " A=0x" << std::hex << (int)regs._a
                              << " F=0x" << (int)regs.flags.get_byte()
                              << " BC=0x" << regs.read_register(REG_TYPE::RT_BC)
                              << " DE=0x" << regs.read_register(REG_TYPE::RT_DE)
                              << " HL=0x" << regs.read_register(REG_TYPE::RT_HL)
                              << " SP=0x" << regs.read_register(REG_TYPE::RT_SP)
                              << " PC=0x" << regs.read_register(REG_TYPE::RT_PC) << std::dec << std::endl;
                    return status;
                }
            }
        }
        std::cout << std::endl << "Headless run finished after " << updates << " instructions." << std::endl;
        return 0;
    }

    const unsigned int DEBUG_WIDTH = 1200;
    const unsigned int DEBUG_HEIGHT = 720;
    const unsigned int GAME_SCALE = 5;
    const unsigned int GAME_WIDTH = 160 * GAME_SCALE;
    const unsigned int GAME_HEIGHT = 144 * GAME_SCALE;

    std::cout << "Current SFML Version " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;

    sf::RenderWindow debugger_window(sf::VideoMode({DEBUG_WIDTH, DEBUG_HEIGHT}), "GB-Debugger");
    sf::RenderWindow game_window(sf::VideoMode({GAME_WIDTH, GAME_HEIGHT}), "GB-Emulator");

    game_window.setPosition(sf::Vector2i(100, 100));
    debugger_window.setPosition(sf::Vector2i(100 + GAME_WIDTH + 100, 400));

    if (!ImGui::SFML::Init(debugger_window)) {
        std::cerr << "Failed to initialize ImGui-SFML" << std::endl;
        return -1;
    }

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    
    ImFontConfig fontConfig;
    fontConfig.FontDataOwnedByAtlas = false;

    io.Fonts->AddFontFromMemoryTTF(
        (void*)__JetBrainsMono_Medium_ttf,
        __JetBrainsMono_Medium_ttf_len,
        18.0f,
        &fontConfig
    );

    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    if (!ImGui::SFML::UpdateFontTexture()) {
        std::cerr << "Failed to update font texture" << std::endl;
        return -1;
    }

    init_instructions();

    Debugger debugger(inputRom);

	SoundStream audio_stream(debugger.getAPU()->getAudioBuffer());
	audio_stream.play();

    sf::Texture game_texture;

    if (!game_texture.resize({160, 144})) {
        std::cerr << "Failed to create game texture" << std::endl;
        return -1;
    }

    sf::Sprite game_sprite(game_texture);

    game_sprite.setScale({static_cast<float>(GAME_SCALE), static_cast<float>(GAME_SCALE)});

    std::array<uint32_t, 160 * 144> game_buffer;

    sf::Clock deltaClock;


    while (debugger_window.isOpen() && game_window.isOpen()){

        while (const std::optional event = debugger_window.pollEvent()) {
            ImGui::SFML::ProcessEvent(debugger_window, *event);

            if (event->is<sf::Event::Closed>()) {
                debugger_window.close();
            }
        }

        std::optional<sf::Event> event;
        while (event = game_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                game_window.close();
            }

            else if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                debugger.handle_input(keyEvent->code, true);
            }
            else if (const auto* keyEvent = event->getIf<sf::Event::KeyReleased>()) {
                debugger.handle_input(keyEvent->code, false);
            }
        }

        ImGui::SFML::Update(debugger_window, deltaClock.restart());
        debugger.render();

        debugger.get_video_buffer(game_buffer);

        game_texture.update(reinterpret_cast<const std::uint8_t*>(game_buffer.data()));

        debugger_window.clear(sf::Color::Black);
        ImGui::SFML::Render(debugger_window);
        debugger_window.display();

        game_window.clear(sf::Color::Black);
        game_window.draw(game_sprite);
        game_window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}