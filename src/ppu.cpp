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

void PicturePU::dma_tick(uint8_t cycles) {
	while (cycles --) {
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
			// std::cout << "DMA done!\n" << std::endl;
			_sleep(2);
		}
	}
}

bool PicturePU::dma_transferring() {
	return dma.active;
}

bool PicturePU::LCDC_BGW_enabled() {
	return (LCDC & (1 << 0)) != 0;
}

uint16_t PicturePU::LCDC_BGW_data_area() {
	if ((LCDC & (1 << 4)) == 1) {
		return 0x8000;
	}
	return 0x8800;
}

uint16_t PicturePU::LCDC_BG_map_area() {
	if (LCDC & (1 << 3)) {
		return 0x9C00;
	}
	return 0x9800;
}

bool PicturePU::LCDC_OBJ_enabled() {
	return (LCDC & (1 << 1)) != 0;
}

uint8_t PicturePU::LCDC_OBJ_height() {
	if (LCDC & (1 << 2)) {
		return 16;
	}
	return 8;
}

bool PicturePU::LCDC_WINDOW_enabled() {
	return (LCDC & (1 << 5)) != 0;
}

uint8_t PicturePU::LCDC_WINDOW_map_area() {
	if (LCDC & (1 << 6)) {
		return 0x9C00;
	}
	return 0x9800;
}

bool PicturePU::LCDC_LCD_enabled() {
	return (LCDC & (1 << 7)) != 0;
}

LCD_MODE PicturePU::LCDS_mode() {
	return (LCD_MODE)(STAT & 0b11);
}

void PicturePU::LCDS_mode_set(LCD_MODE mode) {
	STAT = (STAT & 0b11111100) | (uint8_t)mode;
}

bool PicturePU::LCDS_LYC() {
	return (STAT & (1 << 2)) != 0;
}

void PicturePU::LCDS_LYC_set(bool flag) {
	if (flag) {
		STAT |= (1 << 2);
	} else {
		STAT &= ~(1 << 2);
	}
}

bool PicturePU::LCDS_STAT_int(uint8_t value) {
	if (STAT & (value)) {
		return true;
	}
	return false;
}

void PicturePU::update_palettes(uint8_t value, uint8_t pal) {
	uint32_t *colors = bg_colors;
	if (pal == 1) {
		colors = sp1_colors;
	} else if (pal == 2) {
		colors = sp2_colors;
	}

	colors[0] = default_colors[value & 0b11];
	colors[1] = default_colors[(value >> 2) & 0b11];
	colors[2] = default_colors[(value >> 4) & 0b11];
	colors[3] = default_colors[(value >> 6) & 0b11];
}


uint8_t PicturePU::LCD_read(uint16_t address) {
	uint8_t offset = address - LCDC_ADDR;
	switch (offset) {
		case 0x00: return LCDC;
		case 0x01: return STAT;
		case 0x02: return SCY;
		case 0x03: return SCX;
		case 0x04: return LY;
		case 0x05: return LYC;
		case 0x06: return DMA;
		case 0x07: return BGP;
		case 0x08: return OBP0;
		case 0x09: return OBP1;
		case 0x0A: return WY;
		case 0x0B: return WX;
		default:
			std::cout << "Unimplemented LCD read at address: " << std::hex << address << std::dec << std::endl;
			return 0;
	}
}

void PicturePU::LCD_write(uint16_t address, const uint8_t value) {
	uint8_t offset = address - LCDC_ADDR;
	switch (offset) {
		case 0x00: LCDC = value; break;
		case 0x01: STAT = value; break;
		case 0x02: SCY = value;	break;
		case 0x03: SCX = value;	break;
		case 0x04: LY = value;	break;
		case 0x05: LYC = value;  break;
		case 0x06: DMA = value;  break;
		case 0x07: BGP = value;  break;
		case 0x08: OBP0 = value; break;
		case 0x09: OBP1 = value;	break;
		case 0x0A: WY = value;	break;
		case 0x0B: WX = value;	break;
		default:
			std::cout << "Unimplemented LCD write at address: " << std::hex << address << std::dec << std::endl;
	}
	if (address == DMA_ADDR) {
		dma_start(value);
	}

	if (address == BGP_ADDR) {
		update_palettes(value, 0);
	}
	else if (address == OBP0_ADDR) {
		update_palettes(value & 0b11111100, 1);

	}
	else if (address == OBP1_ADDR) {
		update_palettes(value & 0b11111100, 2);
	}
}