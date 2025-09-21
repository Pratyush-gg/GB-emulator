#include "../include/interrupt.hpp"

void InterruptHandler::interruptRequest(const InterruptType type) {
	interruptFlags |= type;
}

uint8_t InterruptHandler::interruptHandle() {
	static constexpr uint8_t VBLANK_ADDR = 0x40;
	static constexpr uint8_t STAT_ADDR = 0x48;
	static constexpr uint8_t TIMER_ADDR = 0x50;
	static constexpr uint8_t SERIAL_ADDR = 0x58;
	static constexpr uint8_t JOYPAD_ADDR = 0x60;

	const uint8_t required_interrupts = this->interruptEnable & this->interruptFlags;
	if (!interruptMasterEnable || required_interrupts == 0) return 0;

	this->interruptMasterEnable = false; // IME reset

	if (required_interrupts & InterruptType::IT_VBLANK) {
		this->interruptFlags &= ~IT_VBLANK;
		return VBLANK_ADDR;
	}
	if (required_interrupts & InterruptType::IT_LCD_STAT) {
		this->interruptFlags &= ~IT_LCD_STAT;
		return STAT_ADDR;
	}
	if (required_interrupts & InterruptType::IT_TIMER) {
		this->interruptFlags &= ~IT_TIMER;
		return TIMER_ADDR;
	}
	if (required_interrupts & InterruptType::IT_SERIAL) {
		this->interruptFlags &= ~IT_SERIAL;
		return SERIAL_ADDR;
	}
	if (required_interrupts & InterruptType::IT_JOYPAD) {
		this->interruptFlags &= ~IT_JOYPAD;
		return JOYPAD_ADDR;
	}
	return 0;
}
