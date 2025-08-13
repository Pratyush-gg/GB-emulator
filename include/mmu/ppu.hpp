#pragma once
#include <cstdint>
#include <array>

class PicturePU {
	static constexpr uint16_t VRAM_OFFSET = 0x8000;
	static constexpr uint16_t VRAM_SIZE = 0x2000; // 8 KiB

	static constexpr uint16_t OAM_OFFSET = 0xFE00;
	static constexpr uint16_t OAM_SIZE = 0xA0;

	std::array<uint8_t, VRAM_SIZE> vram;
	std::array<uint8_t, OAM_SIZE> oam;
public:
	uint8_t read_vram(uint16_t address);
	void write_vram(uint16_t address, uint8_t value);

	uint8_t read_oam(uint16_t address);
	void write_oam(uint16_t address, uint8_t value);

	uint8_t io_read(uint16_t address);
	void io_write(uint16_t address, uint8_t value);
};