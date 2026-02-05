#pragma once

#include <iostream>
#include <cstdint>
#include <SFML/System.hpp>

inline void not_implemented(const char* function_name) {
    std::cerr << "Function not implemented: " << function_name << std::endl;
    // std::exit(EXIT_FAILURE);
}

inline uint32_t get_ticks() {
    static sf::Clock clock;
    return clock.getElapsedTime().asMilliseconds();
}

inline void delay(uint32_t ms) {
    sf::sleep(sf::milliseconds(ms));
}