#pragma once
#include <cstdint>
#include <memory>
#include <functional>
#include "interrupt.hpp"

class Timer {
    uint16_t dividerRegister = 0xABCC; // 0xff04 DIV
    uint8_t timerCounter = 0; // 0xff05 TIMA
    uint8_t timerModulo = 0; // 0xff06 TMA
    uint8_t timerControl = 0; // 0xff07 TAC

    std::shared_ptr<InterruptHandler> interruptHandler;
    std::function<void()> divApuCallback;

    void incrementTIMA();

public:
    explicit Timer(const std::shared_ptr<InterruptHandler> &interrupt) : interruptHandler(interrupt) {}

    void tick(int cycles);
    uint8_t readAddr(uint16_t address) const;
    void writeAddr(uint16_t address, uint8_t value);
    void setDivApuCallback(std::function<void()> callback) {
        divApuCallback = std::move(callback);
    }
};
