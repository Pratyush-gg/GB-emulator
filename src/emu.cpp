#include "../include/emu.hpp"
#include "../include/mmu.hpp"

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

Emulator::Emulator(const std::string& rom_filename):
    running(true),
    paused(false),
    cycles(0) {
    // TODO: implement the other components required for MMU lmao
    cart = std::make_shared<Cartridge>(rom_filename);
    // ppu = std::make_shared<PicturePU>();
    // apu = std::make_shared<AudioPU>();
    // timer = std::make_shared<Timer>();
    // joypad = std::make_shared<JoyPad>();
    bus = std::make_shared<MMU>(cart);
    cpu = std::make_shared<CPU>(bus);

    // TODO: implement the SDL shit and also declare it as a member variable
}

void Emulator::run() {

    while (running) {
        if (paused) {
            continue;
        }
        // pollInput();
        updateState();
        // renderScreen();

        if (!running) {
            break;
        }
    }
}

void Emulator::updateState() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    int increment_cycles = cpu->cpu_step();
    if (increment_cycles == 0) {
        std::cout << "CPU stopped." << std::endl;
        running = false;
        return;
    }
    cycles += increment_cycles;
}

Emulator::~Emulator() {
    // TODO
}