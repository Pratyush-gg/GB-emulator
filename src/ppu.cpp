#include "../include/ppu.hpp"

#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "../include/mmu.hpp"

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
		case SCY_ADDR 	: return SCY;
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
		case LCDC_ADDR	: LCDC = value; break;
		case STAT_ADDR	: STAT = value; break;
		case SCX_ADDR 	: SCX = value;	break;
		case SCY_ADDR 	: SCY = value;	break;
		case LY_ADDR  	: LY = value;	break;
		case LYC_ADDR 	: LYC = value;  break;
		case DMA_ADDR 	: DMA = value;  break;
		case BGP_ADDR 	: BGP = value;  break;
		case OBP0_ADDR	: OBP0 = value; break;
		case OBP1_ADDR	: OBP1 = value;	break;
		case WY_ADDR  	: WY = value;	break;
		case WX_ADDR  	: WX = value;	break;
		default:
			std::cout << "Unimplemented I/oooo write at address: " << std::hex << address << std::dec << std::endl;
	}
}

void PicturePU::tick(unsigned cycles) {
	clock += cycles;
}

void PicturePU::dma_start(const uint8_t value) {
	dma.active = true;
	dma.byte = 0;
	dma.start_delay = 2;
	dma.value = value;
}

void PicturePU::dma_tick() {
	if (!dma.active) return;

	if (dma.start_delay > 0) {
		dma.start_delay--;
		return;
	}

    if (std::shared_ptr<MMU> tempBus = bus.lock()) {
        write_oam(dma.byte, tempBus->read_data((dma.value * 0x100) + dma.byte));
    }
	dma.byte++;

	dma.active = dma.byte < 0xA0;

	if (!dma.active) {
		std::cout << "DMA transfer complete" << std::endl;
	}
}

bool PicturePU::dma_transferring() {
	return dma.active;
}