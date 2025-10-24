#include "../include/ppu.hpp"

#include <iostream>
#include <cstdint>
#include <stdexcept>
#include "../include/mmu.hpp"
#include "../include/interrupt.hpp"
#include "../include/gb_utils.hpp"

static uint32_t target_frame_time = 1000 / 60;
static long prev_frame_time = 0;
static long start_timer = 0;
static long frame_count = 0;

PicturePU::PicturePU(std::shared_ptr<InterruptHandler> interruptHandler) {
	this->interruptHandler = interruptHandler;
}

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
	}
}

bool PicturePU::dma_transferring() {
	return dma.active;
}

void PicturePU::increment_LY() {
	LY++;
	if (LY == LYC) {
		LCDS_LYC_set(true);
		if (LCDS_STAT_int(SS_LYC)) {
			interruptHandler->interruptRequest(IT_LCD_STAT);
		}
	} else {
		LCDS_LYC_set(false);
	}
}

bool PicturePU::pipeline_queue_add() {
	if (pixel_fifo.size() > 8) {
		return false;
	}

	int x = fetch_x - (8 - (SCX % 8));
	for (int i = 0; i < 8; ++i) {
		int bit = 7 - i;
		uint8_t high = !!(background_fetch_data[1] & (1 << bit));
		uint8_t low = !!(background_fetch_data[2] & (1 << bit)) << 1;
		uint32_t color_id = bg_colors[high | low];

		if (x >= 0) {
			pixel_fifo.push(color_id);
		}
	}
	return true;
}


void PicturePU::pipeline_push_pixel() {
	if (pixel_fifo.size() > 8) {
		uint32_t pixel_data = pixel_fifo.front();
		pixel_fifo.pop();

		if (line_x >= (SCX % 8)) {
			video_buffer[pushed_x + (LY * SCREEN_WIDTH)] = pixel_data;
			pushed_x++;
		}
		line_x++;
	}
}

void PicturePU::pipeline_fetch() {
	switch (current_fetch_state) {
		case  FS_READ_TILE: {
			if (LCDC_BGW_enabled()) {
				if (std::shared_ptr<MMU> tempBus = bus.lock()) {
					background_fetch_data[0] = tempBus->read_data((LCDC_BG_map_area() + (map_x / 8)) + (map_y / 8) * 32);
				}
				if (LCDC_BGW_data_area() == 0x8000) {
					background_fetch_data[0] += 128;
				}
			}
			current_fetch_state = FS_READ_DATA0;
			fetch_x += 8;
			break;
		}

		case FS_READ_DATA0: {
			if (std::shared_ptr<MMU> tempBus = bus.lock()) {
				background_fetch_data[1] = tempBus->read_data(LCDC_BGW_data_area() + (background_fetch_data[0] * 16) + tile_y);
			}
			current_fetch_state = FS_READ_DATA1;
			break;
		}

		case FS_READ_DATA1: {
			if (std::shared_ptr<MMU> tempBus = bus.lock()) {
				background_fetch_data[2] = tempBus->read_data(LCDC_BGW_data_area() + (background_fetch_data[0] * 16) + tile_y + 1);
			}
			current_fetch_state = FS_SLEEP;
			break;
		}

		case FS_SLEEP: {
			current_fetch_state = FS_PUSH;
			break;
		}

		case FS_PUSH: {
			if (pipeline_queue_add()) {
				current_fetch_state = FS_READ_TILE;
			}
			break;
		}
	}
}

void PicturePU::pipeline_process() {
	map_y = LY + SCY;
	map_x = fetch_x + SCX;
	tile_y = ((LY + SCY) % 8) * 2;

	if (!(line_ticks & 1)) {
		pipeline_fetch();
	}

	pipeline_push_pixel();
}

void PicturePU::ppu_mode_oam() {
	if (line_ticks >= 80) {
		LCDS_mode_set(MODE_XFER);

		current_fetch_state = FS_READ_TILE;
		line_x = 0;
		pushed_x = 0;
		fetch_x = 0;
		fifo_x = 0;
	}
}

void PicturePU::ppu_mode_xfer() {
	pipeline_process();

	if (pushed_x >= SCREEN_WIDTH) {
		while (pixel_fifo.size() > 0) {
			pixel_fifo.pop();
		}
		LCDS_mode_set(MODE_HBLANK);

		if (LCDS_STAT_int(SS_HBLANK)) {
			interruptHandler->interruptRequest(IT_LCD_STAT);
		}
	}
}

void PicturePU::ppu_mode_vblank() {
	if (line_ticks >= TICKS_PER_LINE) {
		increment_LY();

		if (LY >= LINES_PER_FRAME) {
			LCDS_mode_set(MODE_OAM);
			LY = 0;
		}
		line_ticks = 0;
	}
}

void PicturePU::ppu_mode_hblank() {
	if (line_ticks >= TICKS_PER_LINE) {
		increment_LY();

		if (LY >= SCREEN_HEIGHT) {
			LCDS_mode_set(MODE_VBLANK);
			interruptHandler->interruptRequest(IT_VBLANK);

			if (LCDS_STAT_int(SS_VBLANK)) {
				interruptHandler->interruptRequest(IT_LCD_STAT);
			}
			current_frame++;
			uint32_t end = get_ticks();
			uint32_t frame_time = end - prev_frame_time;

			if (frame_time < target_frame_time) {
				delay(target_frame_time - frame_time);
			}

			if (end - start_timer >= 1000) {
				uint32_t fps = frame_count;
				start_timer = end;
				frame_count = 0;

				std::cout << "FPS: " << fps << std::endl;
			}

			frame_count++;
			prev_frame_time = get_ticks();
		}
		else {
			LCDS_mode_set(MODE_OAM);
		}
		line_ticks = 0;
	}
}

void PicturePU::ppu_tick(unsigned cycles) {
	while (cycles --) {
		line_ticks++;
		switch (LCDS_mode()) {
			case MODE_OAM:
				ppu_mode_oam();
				break;
			case MODE_XFER:
				ppu_mode_xfer();
				break;
			case MODE_HBLANK:
				ppu_mode_hblank();
				break;
			case MODE_VBLANK:
				ppu_mode_vblank();
				break;
		}
	}
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

uint16_t PicturePU::LCDC_WINDOW_map_area() {
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
		update_palettes(value & 0b11111100, 1);
	}
}