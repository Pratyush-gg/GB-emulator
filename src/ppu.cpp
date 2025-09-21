#include "../include/ppu.hpp"

#include <iostream>
#include <cstdint>
#include <stdexcept>

uint8_t PicturePU::read_vram(const uint16_t address) const {
	if (address < VRAM_OFFSET || address >= VRAM_OFFSET + VRAM_SIZE)
		throw std::out_of_range("VRAM read out of bounds");
	return vram[address - VRAM_OFFSET];
}

void PicturePU::write_vram(const uint16_t address, const uint8_t value) {
	if (address < VRAM_OFFSET || address >= VRAM_OFFSET + VRAM_SIZE)
		throw std::out_of_range("VRAM write out of bounds");
	vram[address - VRAM_OFFSET] = value;
}

uint8_t PicturePU::read_oam(const uint16_t address) const {
	if (address < OAM_OFFSET || address >= OAM_OFFSET + OAM_SIZE)
		throw std::out_of_range("OAM read out of bounds");
	return oam[address - OAM_OFFSET];
}

void PicturePU::write_oam(const uint16_t address, const uint8_t value) {
	if (address < OAM_OFFSET || address >= OAM_OFFSET + OAM_SIZE)
		throw std::out_of_range("OAM write out of bounds");
	oam[address - OAM_OFFSET] = value;
}

uint8_t PicturePU::io_read(const uint16_t address) const {
	switch(address) {
		case LCDC_ADDR	: return LCDC;
		case STAT_ADDR	: return STAT;
		case SCX_ADDR 	: return SCX;
		case LY_ADDR  	: return LY;
		case LYC_ADDR 	: return LYC;
		case DMA_ADDR 	: return DMA;
		case BGP_ADDR 	: return BGP;
		case OBP0_ADDR	: return WY;
		case OBP1_ADDR	: return OBP1;
		case WY_ADDR  	: return WY;
		case WX_ADDR  	: return WX;
		default: return 0;
	}
}

void PicturePU::io_write(const uint16_t address, const uint8_t value) {
	 switch (address) {
		case LCDC_ADDR	: LCDC = value;
		case STAT_ADDR	: STAT = value;
		case SCX_ADDR 	: SCX = value;
		case LY_ADDR  	: LY = value;
		case LYC_ADDR 	: LYC = value;
		case DMA_ADDR 	: DMA = value;
		case BGP_ADDR 	: BGP = value;
		case OBP0_ADDR	: OBP0 = value;
		case OBP1_ADDR	: OBP1 = value;
		case WY_ADDR  	: WY = value;
		case WX_ADDR  	: WX = value;
		default:
			std::cout << "Unimplemented I/O write at address: " << std::hex << address << std::dec << std::endl;
	}
}