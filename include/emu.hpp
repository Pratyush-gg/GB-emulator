#pragma once
#include <cstdint>
#include <memory>
#include <array>

#include "cpu.hpp"
#include "mmu.hpp"
#include "cart.hpp"
#include "ppu.hpp"
#include "timer.hpp"
#include "interrupt.hpp"
#include "joypad.hpp"

struct DebugContext {
    std::reference_wrapper<const MMU> mmu;
    std::reference_wrapper<const RegisterFile> regs;

    DebugContext(std::reference_wrapper<const MMU> mmu,
        std::reference_wrapper<const RegisterFile> regs) :
        mmu(mmu), regs(regs) {}
};

class Emulator {
    bool running;
    bool paused;

    std::shared_ptr<CPU> cpu;
    std::shared_ptr<MMU> bus;
    std::shared_ptr<Cartridge> cart;
    std::shared_ptr<PicturePU> ppu;
    // std::shared_ptr<AudioPU> apu;
    std::shared_ptr<Timer> timer;
    std::shared_ptr<InterruptHandler> interrupts;
    std::shared_ptr<JoyPad> joypad;

    void pollInput();
    void updateState();
    void renderScreen();
    void handleCycles() const;

public:
    explicit Emulator(const std::string& rom_filename);
    void run();
    void run_one();

    uint32_t getCurrentFrame() const;

    DebugContext getDebugContext() const;

    std::shared_ptr<JoyPad> getJoyPad() {
        return joypad;
    }

    const std::array<uint32_t, 160 * 144>& get_emu_video_buffer() const;
};
