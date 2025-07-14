#pragma once
#include "cart.hpp"

#include <cstdint>
#include <memory>

// TODO: Implement all this one by one
class PicturePU;
class AudioPU;
class Timer;
class JoyPad;

class MMU {
private:
    std::shared_ptr<Cartridge> cartridge;
    // std::shared_ptr<PicturePU> ppu;
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
