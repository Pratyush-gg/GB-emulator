#pragma once
#include <cstdint>
#include <array>

class PicturePU {
	static constexpr uint16_t VRAM_OFFSET = 0x8000;
	static constexpr uint16_t VRAM_SIZE = 0x2000; // 8 KiB

	static constexpr uint16_t OAM_OFFSET = 0xFE00;
	static constexpr uint16_t OAM_SIZE = 0xA0;

	std::array<uint8_t, VRAM_SIZE> vram = {};
	std::array<uint8_t, OAM_SIZE> oam = {};

	/*
	0xFF40 – LCDC   (LCD Control)
	0xFF41 – STAT   (LCD Status)
	0xFF42 – SCY    (Scroll Y)
	0xFF43 – SCX    (Scroll X)
	0xFF44 – LY     (LCD Y Coordinate, current scanline)
	0xFF45 – LYC    (LY Compare)
	0xFF46 – DMA    (OAM DMA transfer start)
	0xFF47 – BGP    (Background Palette)
	0xFF48 – OBP0   (Object Palette 0)
	0xFF49 – OBP1   (Object Palette 1)
	0xFF4A – WY     (Window Y Position)
	0xFF4B – WX     (Window X Position, minus 7)
	*/

	static constexpr uint16_t LCDC_ADDR = 0XFF40;
	static constexpr uint16_t STAT_ADDR = 0xFF41;
	static constexpr uint16_t SCY_ADDR	= 0xFF42;
	static constexpr uint16_t SCX_ADDR  = 0xFF43;
	static constexpr uint16_t LY_ADDR   = 0xFF44;
	static constexpr uint16_t LYC_ADDR  = 0xFF45;
	static constexpr uint16_t DMA_ADDR  = 0xFF46;
	static constexpr uint16_t BGP_ADDR  = 0xFF47;
	static constexpr uint16_t OBP0_ADDR = 0xFF48;
	static constexpr uint16_t OBP1_ADDR = 0xFF49;
	static constexpr uint16_t WY_ADDR	= 0xFF4A;
	static constexpr uint16_t WX_ADDR   = 0xFF4B;

	uint8_t LCDC = 0;
	uint8_t STAT = 0;
	uint8_t SCY = 0;
	uint8_t SCX = 0;
	uint8_t LY  = 0;
	uint8_t LYC = 0;
	uint8_t DMA = 0;
	uint8_t BGP = 0;
	uint8_t OBP0 = 0;
	uint8_t OBP1 = 0;
	uint8_t WY  = 0;
	uint8_t WX  = 0;

public:
	uint8_t read_vram(uint16_t address) const;
	void write_vram(uint16_t address, uint8_t value);

	uint8_t read_oam(uint16_t address) const;
	void write_oam(uint16_t address, uint8_t value);

	uint8_t io_read(uint16_t address) const;
	void io_write(uint16_t address, uint8_t value);
};