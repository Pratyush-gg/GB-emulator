#include "../include/mmu/ppu.hpp"
#include "../include/cpu.hpp"


#include <iostream>
#include <cstdint>
#include <stdexcept>

char serial_data[2];

uint8_t PicturePU::read_vram(uint16_t address) {
	if (address < VRAM_OFFSET || address >= VRAM_OFFSET + VRAM_SIZE)
		throw std::out_of_range("VRAM read out of bounds");
	return vram[address - VRAM_OFFSET];
}

void PicturePU::write_vram(uint16_t address, uint8_t value) {
	if (address < VRAM_OFFSET || address >= VRAM_OFFSET + VRAM_SIZE)
		throw std::out_of_range("VRAM write out of bounds");
	vram[address - VRAM_OFFSET] = value;
}

uint8_t PicturePU::read_oam(uint16_t address) {
	if (address < OAM_OFFSET || address >= OAM_OFFSET + OAM_SIZE)
		throw std::out_of_range("OAM read out of bounds");
	return oam[address - OAM_OFFSET];
}

void PicturePU::write_oam(uint16_t address, uint8_t value) {
	if (address < OAM_OFFSET || address >= OAM_OFFSET + OAM_SIZE)
		throw std::out_of_range("OAM write out of bounds");
	oam[address - OAM_OFFSET] = value;
}

uint8_t PicturePU::io_read(uint16_t address) {
	if (address == 0xFF01) {
		return serial_data[0];
	}
	if (address == 0xFF02) {
		return serial_data[1];
	}
	if (address >= 0xFF04 && address < 0xFF07) {
		return cpu->timerRead(address);
	}
	if (address == 0xFF0F) {
		return cpu.interrupt_flags;
	}
	std::cout << "Unimplemented I/O read at address: " << std::hex << address << std::dec << std::endl;
	return 0;
}

void PicturePU::io_write(uint16_t address, uint8_t value) {
	if (address == 0xFF01) {
		serial_data[0] = value;
		return;
	}
	if (address == 0xFF02) {
		serial_data[1] = value;
		return;
	}
	if (address >= 0xFF04 && address < 0xFF07) {
		cpu.timerWrite(address, value);
		return;
	}
	if (address == 0xFF0F) {
		cpu.interrupt_flags = value;
		return;
	}
	std::cout << "Unimplemented I/O write at address: " << std::hex << address << std::dec << std::endl;
}
