#pragma once
#include <cstdint>
#include  <memory>

class CPU;

enum InterruptType {
	IT_VBLANK	= 1,
	IT_LCD_STAT = 2,
	IT_TIMER	= 4,
	IT_SERIAL	= 8,
	IT_JOYPAD	= 16,
};

class InterruptHandler {
public:
	void setCPU(const std::weak_ptr<CPU> &cpuPtr);

	uint8_t IE = 0x00;
	uint8_t IF = 0b11100000;
	bool IME = false;

	std::weak_ptr<CPU> cpu;

	void interruptRequest(InterruptType type);
	void interruptHandle();
	bool interruptCheck(uint16_t address, InterruptType type);

	inline bool hasPendingInterrupt() const {
		return IF;
	}
};