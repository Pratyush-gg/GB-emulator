#include "../include/mmu/ppu.hpp"

#include <cstdint>
#include <stdexcept>

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
