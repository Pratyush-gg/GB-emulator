#pragma once
#include <cstdint>
#include <memory>

#include "cpu.hpp"

class Emulator {
private:
    bool running;
    bool paused;
    uint64_t cycles;

    std::shared_ptr<CPU> cpu;
    std::shared_ptr<MMU> bus;
    std::shared_ptr<Cartridge> cart;

    void pollInput();
    void updateState();
    void renderScreen();

    // add extra SDL shit

public:
    Emulator(const std::string& rom_filename);
    ~Emulator();

    void run();
};
