#include "debugger.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include "../include/emu.hpp"
#include "../include/instructions.hpp"

#include "SFML/Graphics.hpp"
#include <iostream>
#include "../fonts/ttf/JetBrainsMono-Medium.h"

int main(int argc, char* argv[]) {

    sf::RenderWindow window(sf::VideoMode({1200, 720}), "GB-Debugger");

    ImGui::SFML::Init(window);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromMemoryTTF(__JetBrainsMono_Medium_ttf, __JetBrainsMono_Medium_ttf_len, 16.0f);

    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::SFML::UpdateFontTexture();

    auto emulator = std::make_shared<Emulator>(argv[1]);
    init_instructions();

    Debugger debugger(emulator);

    sf::Clock deltaClock;

    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        debugger.render();

        window.clear(sf::Color::Black);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}