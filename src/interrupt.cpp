#include "../include/interrupt.hpp"

void InterruptHandler::interruptRequest(InterruptType type) {
	interruptFlags |= type;
}

uint8_t InterruptHandler::interruptHandle() {
	if (!interruptMasterEnable) return 0;

	static const uint8_t VBLANK_ADDR = 0x40;
	static const uint8_t STAT_ADDR = 0x48;
	static const uint8_t TIMER_ADDR = 0x50;
	static const uint8_t SERIAL_ADDR = 0x58;
	static const uint8_t JOYPAD_ADDR = 0x60;

	uint8_t required_interrupts = this->interruptEnable & this->interruptFlags;

	this->interruptMasterEnable = false; // IME reset

	if (required_interrupts & InterruptType::IT_VBLANK) {
		this->interruptFlags ^= IT_VBLANK;
		return VBLANK_ADDR;
	}
	if (required_interrupts & InterruptType::IT_LCD_STAT) {
		this->interruptFlags ^= IT_LCD_STAT;
		return STAT_ADDR;
	}
	if (required_interrupts & InterruptType::IT_TIMER) {
		this->interruptFlags ^= IT_TIMER;
		return TIMER_ADDR;
	}
	if (required_interrupts & InterruptType::IT_SERIAL) {
		this->interruptFlags ^= IT_SERIAL;
		return SERIAL_ADDR;
	}
	if (required_interrupts & InterruptType::IT_JOYPAD) {
		this->interruptFlags ^= IT_JOYPAD;
		return JOYPAD_ADDR;
	}
}
