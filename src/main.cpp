#include "debugger.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include "../include/emu.hpp"
#include "../include/instructions.hpp"

#include "SFML/Graphics.hpp"
#include <iostream>
#include <array>

#include "ppu.hpp"
#include "../fonts/ttf/JetBrainsMono-Medium.h"

int main(int argc, char* argv[]) {

    const unsigned int DEBUG_WIDTH = 1200;
    const unsigned int DEBUG_HEIGHT = 720;
    const unsigned int GAME_SCALE = 5;
    const unsigned int GAME_WIDTH = 160 * GAME_SCALE;
    const unsigned int GAME_HEIGHT = 144 * GAME_SCALE;

    sf::RenderWindow debugger_window(sf::VideoMode({DEBUG_WIDTH, DEBUG_HEIGHT}), "GB-Debugger");
    sf::RenderWindow game_window(sf::VideoMode({GAME_WIDTH, GAME_HEIGHT}), "GB-Emulator");

    game_window.setPosition(sf::Vector2i(100, 100));
    debugger_window.setPosition(sf::Vector2i(100 + GAME_WIDTH + 100, 400));

    ImGui::SFML::Init(debugger_window);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromMemoryTTF(__JetBrainsMono_Medium_ttf, __JetBrainsMono_Medium_ttf_len, 18.0f);

    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::SFML::UpdateFontTexture();

    init_instructions();

    Debugger debugger(argv[1]);

    sf::Texture game_texture;
    game_texture.create(160, 144);
    sf::Sprite game_sprite(game_texture);
    game_sprite.setScale((GAME_SCALE), (GAME_SCALE));

    std::array<uint32_t, 160 * 144> game_buffer;

    sf::Clock deltaClock;

    while (debugger_window.isOpen() && game_window.isOpen()){
        sf::Event event{};
        while (debugger_window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(debugger_window, event);
            if (event.type == sf::Event::Closed) {
                debugger_window.close();
            }
        }

        while (game_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                game_window.close();
            }
        }

        ImGui::SFML::Update(debugger_window, deltaClock.restart());
        debugger.render();

        debugger.get_video_buffer(game_buffer);

        game_texture.update(reinterpret_cast<const sf::Uint8*>(game_buffer.data()));

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