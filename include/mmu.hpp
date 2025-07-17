#pragma once
#include "cart.hpp"
#include "mmu/ppu.hpp"

#include <cstdint>
#include <memory>

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
class AudioPU;
class Timer;
class JoyPad;

class MMU {
private:
    std::shared_ptr<Cartridge> cartridge;
    std::shared_ptr<PicturePU> ppu;
    // std::shared_ptr<AudioPU> apu;
    // std::shared_ptr<Timer> timer;
    // std::shared_ptr<JoyPad> joypad;

public:
    MMU(std::shared_ptr<Cartridge> _cartridge
        // std::shared_ptr<PicturePU> _ppu,
        // std::shared_ptr<AudioPU> _apu,
        // std::shared_ptr<Timer> _timer,
        // std::shared_ptr<JoyPad> _joypad
        ) :
        cartridge(_cartridge)
        // ppu(_ppu),
        // apu(_apu),
        // timer(_timer),
        // joypad(_joypad)
    {}
    uint8_t read_data(uint16_t address);
    void write_data(uint16_t, uint8_t value);
    uint16_t read_data16(uint16_t address);
    void write_data16(uint16_t address, uint16_t value);
};
