#include "debugger.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#include "../include/emu.hpp"
#include "../include/instructions.hpp"

#include "SFML/Graphics.hpp"
#include <iostream>

int main(int argc, char* argv[]) {

    sf::RenderWindow window(sf::VideoMode({1200, 720}), "GB-emulator");

    ImGui::SFML::Init(window);


    const ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    ImFontConfig fontConfig;
    fontConfig.SizePixels = 15.0f;
    io.Fonts->AddFontDefault(&fontConfig);
    ImGui::SFML::UpdateFontTexture();

    auto emulator = std::make_shared<Emulator>(argv[1]);
    init_instructions();

    Debugger debugger(emulator);

    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // std::cout << "in loop :>" << std::endl;

        ImGui::SFML::Update(window, deltaClock.restart());

        debugger.render();

        window.clear(sf::Color::Black);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}