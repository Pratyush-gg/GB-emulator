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


	uint8_t interruptEnable = 0x00;      // IE
	uint8_t interruptFlags = 0b11100000; // IF
	bool interruptMasterEnable = false;  // IME

	void interruptRequest(InterruptType type);
	uint8_t interruptHandle();
};