#include "../include/interrupt.hpp"

void InterruptHandler::interruptRequest(const InterruptType type) {
	IF |= type;
}

uint8_t InterruptHandler::interruptHandle() {
	static constexpr uint8_t VBLANK_ADDR = 0x40;
	static constexpr uint8_t STAT_ADDR = 0x48;
	static constexpr uint8_t TIMER_ADDR = 0x50;
	static constexpr uint8_t SERIAL_ADDR = 0x58;
	static constexpr uint8_t JOYPAD_ADDR = 0x60;

	const uint8_t required_interrupts = this->IE & this->IF;
	if (!IME || required_interrupts == 0) return 0;

	this->IME = false; // IME reset

	if (required_interrupts & InterruptType::IT_VBLANK) {
		this->IF &= ~IT_VBLANK;
		return VBLANK_ADDR;
	}
	if (required_interrupts & InterruptType::IT_LCD_STAT) {
		this->IF &= ~IT_LCD_STAT;
		return STAT_ADDR;
	}
	if (required_interrupts & InterruptType::IT_TIMER) {
		this->IF &= ~IT_TIMER;
		return TIMER_ADDR;
	}
	if (required_interrupts & InterruptType::IT_SERIAL) {
		this->IF &= ~IT_SERIAL;
		return SERIAL_ADDR;
	}
	if (required_interrupts & InterruptType::IT_JOYPAD) {
		this->IF &= ~IT_JOYPAD;
		return JOYPAD_ADDR;
	}
	return 0;
}
