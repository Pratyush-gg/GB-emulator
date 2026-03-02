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
			tempCPU->halted = false;
		}
		IF &= ~type;
		IME = false;

		return true;
	}
	return false;
}

bool InterruptHandler::hasPendingInterrupt() const {
	return (IE & IF & 0x1F) != 0;
}

bool InterruptHandler::interruptHandle() {
	if (InterruptHandler::interruptCheck(0x40, IT_VBLANK)) return true;

	if (InterruptHandler::interruptCheck(0x48, IT_LCD_STAT)) return true;

	if (InterruptHandler::interruptCheck(0x50, IT_TIMER)) return true;

	if (InterruptHandler::interruptCheck(0x58, IT_SERIAL)) return true;

	if (InterruptHandler::interruptCheck(0x60, IT_JOYPAD)) return true;

	return false;
}