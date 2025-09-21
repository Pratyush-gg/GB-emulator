#include "../include/emu.hpp"
#include "../include/mmu.hpp"

#include <iostream>
#include <memory>
#include <chrono>

Emulator::Emulator(const std::string& rom_filename):
    running(true),
    paused(false) {
    cart = std::make_shared<Cartridge>(rom_filename);
    ppu = std::make_shared<PicturePU>();
    // apu = std::make_shared<AudioPU>();
    // timer = std::make_shared<Timer>();
    // joypad = std::make_shared<JoyPad>();
    bus = std::make_shared<MMU>(cart, ppu);
    cpu = std::make_shared<CPU>(bus);
}

void Emulator::run() {
    while (running) {
        if (paused) {
            continue;
        }
        // pollInput();
        updateState();
        // renderScreen();

        if (!this->running) {
            break;
        }
    }
}

void Emulator::updateState() {
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    const int increment_cycles = cpu->cpu_step();
    if (!increment_cycles) {
        std::cout << "CPU stopped." << std::endl;
        this->running = false;
    }
}