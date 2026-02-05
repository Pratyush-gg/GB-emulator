#include "../include/timer.hpp"

void Timer::tick(uint8_t cycles) {
    while (cycles--) {
		const uint16_t prevDiv = this->dividerRegister;
		this->dividerRegister++;

        bool timer_update = false;
 
		switch(this->timerControl & (0b11)) {
			case 0b00:
				timer_update = (prevDiv & (1 << 9)) && (!(dividerRegister & (1 << 9)));
				break;
			case 0b01:
				timer_update = (prevDiv & (1 << 3)) && (!(dividerRegister & (1 << 3)));
				break;
			case 0b10:
				timer_update = (prevDiv & (1 << 5)) && (!(dividerRegister & (1 << 5)));
				break;
			case 0b11:
				timer_update = (prevDiv & (1 << 7)) && (!(dividerRegister & (1 << 7)));
				break;
			default: break;
		}

		if ((timer_update && timerControl & (1 << 2))) {
            timerCounter++;
			if (timerCounter == 0xFF) {
                this->timerCounter = this->timerModulo;
				this->interruptHandler->interruptRequest(InterruptType::IT_TIMER);
			}
		}
    }
}

uint8_t Timer::readAddr(const uint16_t address) const {
    switch (address) {
        case 0xFF04:
            return this->dividerRegister >> 8;
        case 0xFF05:
            return this->timerCounter;
        case 0xFF06:
            return this->timerModulo;
        case 0xFF07:
            return this->timerControl;
		default: return 0;
    }
}

void Timer::writeAddr(const uint16_t address, const uint8_t value) {
    switch (address) {
        case 0xFF04:
            this->dividerRegister = 0;
            break;
        case 0xFF05:
            this->timerCounter = value;
            break;
        case 0xFF06:
            this->timerModulo = value;
            break;
        case 0xFF07:
            this->timerControl = value;
            break;
    	default: break;
    }
}
