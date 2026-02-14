#pragma once

#include "cart.hpp"
#include "timer.hpp"
#include "apu.hpp"

#include <cstdint>
#include <memory>
#include <utility>
#include <array>

// Memory Map
// 0000	3FFF	16 KiB ROM bank 00	From cartridge, usually a fixed bank
// 4000	7FFF	16 KiB ROM Bank 01–NN	From cartridge, switchable bank via mapper (if any)
// 8000	9FFF	8 KiB Video RAM (VRAM)	In CGB mode, switchable bank 0/1
// A000	BFFF	8 KiB External RAM	From cartridge, switchable bank if any
// C000	CFFF	4 KiB Work RAM (WRAM)
// D000	DFFF	4 KiB Work RAM (WRAM)	In CGB mode, switchable bank 1–7
// E000	FDFF	Echo RAM (mirror of C000–DDFF)	Nintendo says use of this area is prohibited.
// FE00	FE9F	Object attribute memory (OAM)
// FEA0	FEFF	Not Usable	Nintendo says use of this area is prohibited.
// FF00	FF7F	I/O Registers
// FF80	FFFE	High RAM (HRAM)
// FFFF	FFFF	Interrupt Enable register (IE)

// TODO: Implement all this one by one
//class AudioPU;
class JoyPad;
class InterruptHandler;
class PicturePU;
class Cartridge;
class Timer;

class MMU {
private:
    std::shared_ptr<Cartridge> cartridge;
    std::shared_ptr<PicturePU> ppu;
    /*std::shared_ptr<AudioPU> apu;*/
    std::shared_ptr<Timer> timer;
    std::shared_ptr<InterruptHandler> interrupt;
    std::shared_ptr<JoyPad> joypad;

    static constexpr uint16_t CART_SEG1_OFFSET = 0;
    static constexpr uint16_t CART_SEG1_SIZE = 0x8000;

    static constexpr uint16_t VRAM_OFFSET = 0x8000;
    static constexpr uint16_t VRAM_SIZE = 0x2000;

    static constexpr uint16_t CART_SEG2_OFFSET = 0xA000;
    static constexpr uint16_t CART_SEG2_SIZE = 0x2000;

	static constexpr uint16_t WRAM_OFFSET = 0xC000;
    static constexpr uint16_t WRAM_SIZE = 0x2000;

    static constexpr uint16_t ERAM_OFFSET = 0xE000;
    static constexpr uint16_t ERAM_SIZE = 0x1E00;

    static constexpr uint16_t OAM_OFFSET = 0xFE00;
    static constexpr uint16_t OAM_SIZE = 0xA0;

	static constexpr uint16_t HRAM_OFFSET = 0xFF80;
	static constexpr uint16_t HRAM_SIZE = 0x007f;

    static constexpr uint16_t FORBIDDEN_OFFSET = 0xFEA0;
    static constexpr uint16_t FORBIDDEN_SIZE = 0x0060;

    static constexpr uint16_t TIMER_OFFSET = 0xFF04;
    static constexpr uint16_t TIMER_END = 0xFF07;

    static constexpr uint16_t PPO_IO_OFFSET = 0xFF40;
    static constexpr uint16_t PPO_IO_END = 0xFF4B;

	std::array<uint8_t, WRAM_SIZE> wram;
	std::array<uint8_t, HRAM_SIZE> hram;

    std::array<uint8_t, 2> serial_data;

public:
    MMU(std::shared_ptr<Cartridge> _cartridge,
        std::shared_ptr<PicturePU> _ppu,
        std::shared_ptr<Timer> _timer,
        std::shared_ptr<InterruptHandler> _interrupt,
        /*std::shared_ptr<AudioPU> _apu,*/
        std::shared_ptr<JoyPad> _joypad
    );

    uint8_t read_data(uint16_t address) const;
    void write_data(uint16_t address, uint8_t value);
    uint16_t read_data16(uint16_t address) const;
    void write_data16(uint16_t address, uint16_t value);
};
