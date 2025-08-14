#pragma once 
#include <cstdint>
#include <memory>
#include "interrupt.hpp"

class Timer {
    uint8_t dividerRegister; // 0xff04 DIV
    uint8_t timerCounter; // 0xff05 TIMA
    uint8_t timerModulo; // 0xff06 TMA
    uint8_t timerControl; // 0xff07 TAC

    std::shared_ptr<InterruptHandler> interruptHandler;

public:
    void tick(uint8_t cycles);
    uint8_t readAddr(uint16_t address);
    uint8_t writeAddr(uint16_t address, uint8_t value);
};
