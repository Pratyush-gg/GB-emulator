#include "debugger.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include "../include/emu.hpp"
#include "../include/instructions.hpp"

#include "SFML/Graphics.hpp"
#include <iostream>
#include <array>
#include <optional>

#include "ppu.hpp"
#include "../fonts/ttf/JetBrainsMono-Medium.h"

int main(int argc, char* argv[]) {

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
    io.Fonts->AddFontFromMemoryTTF(__JetBrainsMono_Medium_ttf, __JetBrainsMono_Medium_ttf_len, 18.0f);

    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    if (!ImGui::SFML::UpdateFontTexture()) {
        std::cerr << "Failed to update font texture" << std::endl;
        return -1;
    }

    init_instructions();

    std::string inputRom = "C:\\Users\\shawn\\CLionProjects\\GB-emulator\\roms\\Tetris.gb";
    if (argc > 1) inputRom = argv[1];

    Debugger debugger(inputRom);

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