#include "../include/emu.hpp"
#include "../include/mmu.hpp"
#include "../include/ppu.hpp"

#include <iostream>
#include <memory>
#include <chrono>

Emulator::Emulator(const std::string& rom_filename):
    running(true),
    paused(false) {
    cart = std::make_shared<Cartridge>(rom_filename);
    apu = std::make_shared<AudioPU>();
    interrupts = std::make_shared<InterruptHandler>();
    ppu = std::make_shared<PicturePU>(interrupts, cart);
    joypad = std::make_shared<JoyPad>();
    timer = std::make_shared<Timer>(interrupts);
    bus = std::make_shared<MMU>(cart, ppu, timer, interrupts, apu, joypad);
    cpu = std::make_shared<CPU>(bus, interrupts);

    interrupts->setCPU(cpu);

    std::weak_ptr<MMU> PPU_MMU_Pointer(bus);
    ppu->setMMU(PPU_MMU_Pointer);
}

uint32_t Emulator::getCurrentFrame() const {
    return ppu->current_frame;
}

void Emulator::run() {
    while (running) {
        this->run_one();
    }
}

void Emulator::run_one() {
    // pollInput();
    updateState();
    // renderScreen();
}

void Emulator::updateState() {
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    const int increment_cycles = cpu->cpu_step();
    timer->tick(increment_cycles);
    ppu->ppu_tick(increment_cycles);
    ppu->dma_tick(increment_cycles/4);
    apu->tick(increment_cycles);
    if (!increment_cycles) {
        std::cout << "CPU stopped." << std::endl;
        this->running = false;
    }
}

DebugContext Emulator::getDebugContext() const {
    return DebugContext {
         *this->bus,
         this->cpu->getRegisterDebug()
    };
}

const std::array<uint32_t, 160 * 144>& Emulator::get_emu_video_buffer() const {
    return ppu->get_frame_buffer();
}
