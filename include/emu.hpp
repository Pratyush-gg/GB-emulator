#pragma once
#include <cstdint>
#include <memory>

#include "cpu.hpp"
#include "mmu.hpp"
#include "cart.hpp"

class Emulator {
private:
    bool running;
    bool paused;
    uint64_t cycles;

    std::shared_ptr<CPU> cpu;
    std::shared_ptr<MMU> bus;
    std::shared_ptr<Cartridge> cart;
    std::shared_ptr<PicturePU> ppu;
    std::shared_ptr<AudioPU> apu;
    std::shared_ptr<Timer> timer;
    std::shared_ptr<JoyPad> joypad;

    void pollInput();
    void updateState();
    void renderScreen();

    // add extra SDL shit

public:
    Emulator(const std::string& rom_filename);
    ~Emulator();

    void run();
};
