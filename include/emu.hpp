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
    void handleCycles() const;

    // add extra SDL shit

public:
    explicit Emulator(const std::string& rom_filename);

    void run();
};
