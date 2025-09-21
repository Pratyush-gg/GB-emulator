#pragma once
#include <cstdint>

enum InterruptType {
	IT_VBLANK	= 1,
	IT_LCD_STAT = 2,
	IT_TIMER	= 4,
	IT_SERIAL	= 8,
	IT_JOYPAD	= 16,
};

class InterruptHandler {
public:
	uint8_t IE = 0x00;
	uint8_t IF = 0b11100000;
	bool IME = false;

	void interruptRequest(InterruptType type);
	uint8_t interruptHandle();

	inline bool hasPendingInterrupt() const {
		return IF & IE;
	}
};