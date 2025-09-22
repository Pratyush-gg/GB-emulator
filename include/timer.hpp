#pragma once 
#include <cstdint>
#include <memory>
#include "interrupt.hpp"

class Timer {
    uint8_t dividerRegister = 0; // 0xff04 DIV
    uint8_t timerCounter = 0; // 0xff05 TIMA
    uint8_t timerModulo = 0; // 0xff06 TMA
    uint8_t timerControl = 0; // 0xff07 TAC

    std::shared_ptr<InterruptHandler> interruptHandler;

public:
    explicit Timer(const std::shared_ptr<InterruptHandler> &interrupt) : interruptHandler(interrupt) {}

    void tick(uint8_t cycles);
    uint8_t readAddr(uint16_t address) const;
    void writeAddr(uint16_t address, uint8_t value);
};
