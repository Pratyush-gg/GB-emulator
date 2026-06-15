#include "../include/timer.hpp"
#include <iostream>

void Timer::incrementTIMA() {
    timerCounter++;
    if (timerCounter == 0) {
        timerCounter = timerModulo;
        this->interruptHandler->interruptRequest(InterruptType::IT_TIMER);
    }
}

void Timer::tick(int cycles) {
    while (cycles--) {
		const uint16_t prevDiv = this->dividerRegister;
		this->dividerRegister++;
        const bool divApuTick = (prevDiv & (1 << 12)) && !(dividerRegister & (1 << 12));
        if (divApuTick && divApuCallback) {
            divApuCallback();
        }

        static constexpr int bit_positions[4] = { 9, 3, 5, 7 };
        const int sel_bit = bit_positions[this->timerControl & 0x03];

        const bool old_signal = (this->timerControl & (1 << 2)) && (prevDiv & (1 << sel_bit));
        const bool new_signal = (this->timerControl & (1 << 2)) && (this->dividerRegister & (1 << sel_bit));

        if (old_signal && !new_signal) {
            incrementTIMA();
        }
    }
}

uint8_t Timer::readAddr(const uint16_t address) const {
    uint8_t val = 0;
    switch (address) {
        case 0xFF04:
            val = this->dividerRegister >> 8;
            break;
        case 0xFF05:
            val = this->timerCounter;
            break;
        case 0xFF06:
            val = this->timerModulo;
            break;
        case 0xFF07:
            val = this->timerControl;
            break;
		default: val = 0; break;
    }
    return val;
}

void Timer::writeAddr(const uint16_t address, const uint8_t value) {
    switch (address) {
        case 0xFF04: {
			if ((this->dividerRegister & (1 << 12)) && divApuCallback) {
				divApuCallback();
			}
            static constexpr int bit_positions[4] = { 9, 3, 5, 7 };
            const int sel_bit = bit_positions[this->timerControl & 0x03];
            const bool old_signal = (this->timerControl & (1 << 2)) && (this->dividerRegister & (1 << sel_bit));

            this->dividerRegister = 0;

            const bool new_signal = false;

            if (old_signal && !new_signal) {
                incrementTIMA();
            }
            break;
        }
        case 0xFF05:
            this->timerCounter = value;
            break;
        case 0xFF06:
            this->timerModulo = value;
            break;
        case 0xFF07: {
            static constexpr int bit_positions[4] = { 9, 3, 5, 7 };
            const int old_sel_bit = bit_positions[this->timerControl & 0x03];
            const bool old_signal = (this->timerControl & (1 << 2)) && (this->dividerRegister & (1 << old_sel_bit));

            this->timerControl = value;

            const int new_sel_bit = bit_positions[this->timerControl & 0x03];
            const bool new_signal = (this->timerControl & (1 << 2)) && (this->dividerRegister & (1 << new_sel_bit));

            if (old_signal && !new_signal) {
                incrementTIMA();
            }
            break;
        }
    	default: break;
    }
}
