#include "../include/interrupt.hpp"
#include "../include/cpu.hpp"

void InterruptHandler::setCPU(const std::weak_ptr<CPU> &cpuPtr) {
	cpu = cpuPtr;
}

void InterruptHandler::interruptRequest(const InterruptType type) {
	IF |= type;
}

bool InterruptHandler::interruptCheck(uint16_t address, InterruptType type) {
	if ((IE & type) && (IF & type)) {
		if (std::shared_ptr<CPU> tempCPU = cpu.lock()) {
			tempCPU->serviceInterrupt(address);
		}
		IF &= ~type;
		if (std::shared_ptr<CPU> tempCPU = cpu.lock()) {
			tempCPU->halted = false;
		}
		IME = false;

		return true;
	}
	return false;
}

void InterruptHandler::interruptHandle() {
	if (InterruptHandler::interruptCheck(0x40, IT_VBLANK)) return;

	else if (InterruptHandler::interruptCheck(0x48, IT_LCD_STAT)) return;

	else if (InterruptHandler::interruptCheck(0x50, IT_TIMER)) return;

	else if (InterruptHandler::interruptCheck(0x58, IT_SERIAL)) return;

	else if (InterruptHandler::interruptCheck(0x60, IT_JOYPAD)) return;
}