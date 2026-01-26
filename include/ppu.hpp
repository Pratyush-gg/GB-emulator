#pragma once
#include <cstdint>
#include <array>
#include <memory>
#include <queue>

#include "mmu.hpp"

class InterruptHandler;

enum LCD_MODE {
	MODE_VBLANK,
	MODE_HBLANK,
	MODE_OAM,
	MODE_XFER,
};

enum STAT_SOURCES {
	SS_HBLANK = (1 << 3),
	SS_VBLANK = (1 << 4),
	SS_OAM = (1 << 5),
	SS_LYC = (1 << 6),
};

enum FETCH_STATE {
	FS_READ_TILE,
	FS_READ_DATA0,
	FS_READ_DATA1,
	FS_SLEEP,
	FS_PUSH
};

struct oam_entry {
	uint8_t y_pos;
	uint8_t x_pos;
	uint8_t tile_index;
	uint8_t attribute;
};

struct oam_line_entry {
	oam_entry entry;
	struct oam_line_entry *next = nullptr;
};

class PicturePU {

	std::shared_ptr<InterruptHandler> interruptHandler;
	std::shared_ptr<Cartridge> cartridge;

	static constexpr unsigned SCREEN_WIDTH = 160;
	static constexpr unsigned SCREEN_HEIGHT = 144;
	static constexpr unsigned LINES_PER_FRAME = 154;
	static constexpr unsigned TICKS_PER_LINE = 456;

	static constexpr uint16_t VRAM_OFFSET = 0x8000;
	static constexpr uint16_t VRAM_SIZE = 0x2000; // 8 KiB

	static constexpr uint16_t OAM_OFFSET = 0xFE00;
	static constexpr uint16_t OAM_SIZE = 0xA0;



	uint8_t clock = 0;

	std::array<uint8_t, VRAM_SIZE> vram = {};

	std::array<oam_entry, OAM_SIZE / 4> oam_ram = {};

	uint8_t line_sprite_count = 0;
	oam_line_entry *line_sprites = nullptr;
	std::array<oam_line_entry, 10> line_entry_array = {};

	uint8_t fetched_entry_count = 0;
	oam_entry fetched_entry[3];

	uint8_t window_line = 0;

	uint32_t line_ticks = 0;
	std::array<uint32_t, SCREEN_WIDTH * SCREEN_HEIGHT> video_buffer = {0};

	struct DMA {
		bool active;
		uint8_t byte;
		uint8_t value;
		uint8_t start_delay;
	};

	DMA dma{};

	std::queue<uint32_t> pixel_fifo = {};

	FETCH_STATE current_fetch_state = FS_READ_TILE;
	uint8_t line_x = 0;
	uint8_t pushed_x = 0;
	uint8_t fetch_x = 0;
	uint8_t background_fetch_data[3];
	uint8_t fetch_entry_data[6];
	uint8_t map_y;
	uint8_t map_x;
	uint8_t tile_y;
	uint8_t fifo_x;
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

	uint8_t LCDC = 0x91;
	uint8_t STAT = 0;
	uint8_t SCY = 0;
	uint8_t SCX = 0;
	uint8_t LY  = 0;
	uint8_t LYC = 0;
	uint8_t DMA = 0;
	uint8_t BGP = 0xFC;
	uint8_t OBP0 = 0xFF;
	uint8_t OBP1 = 0xFF;
	uint8_t WY  = 0;
	uint8_t WX  = 0;

	uint32_t bg_colors[4] = {};
	uint32_t sp1_colors[4] = {};
	uint32_t sp2_colors[4] = {};

	uint32_t default_colors[4] = {0xFF0FBC9B, 0xFF0FAC8B, 0xFF306230, 0xFF0F380F};

    std::weak_ptr<MMU> bus;

    // PicturePU(const std::weak_ptr<MMU> &_bus) : bus(_bus) {}

public:
	PicturePU(std::shared_ptr<InterruptHandler> handler, std::shared_ptr<Cartridge> cart);

    void setMMU(const std::weak_ptr<MMU> &_bus) {
        bus = _bus;
    }

	const std::array<uint32_t, SCREEN_WIDTH * SCREEN_HEIGHT>& get_frame_buffer() const {
		return video_buffer;
	}

    [[nodiscard]] uint8_t read_vram(uint16_t address) const;
	void write_vram(uint16_t address, uint8_t value);

	[[nodiscard]] uint8_t read_oam(uint16_t address) const;
	void write_oam(uint16_t address, uint8_t value);

	// [[nodiscard]] uint8_t io_read(uint16_t address) const;
	// void io_write(uint16_t address, uint8_t value);

	uint32_t current_frame = 0;

	void increment_LY();
	bool pipeline_queue_add();
	void pipeline_push_pixel();
	void pipeline_fetch();
	void pipeline_process();
	void ppu_tick(unsigned cycles);
	void load_line_sprites();
	void ppu_mode_oam();
	void ppu_mode_xfer();
	void ppu_mode_hblank();
	void ppu_mode_vblank();
	uint32_t fetch_sprite_pixels(int bit, uint32_t color_id, uint8_t bg_color);
	void pipeline_load_sprite_tile();
	void pipeline_load_sprite_data(uint8_t offset);
	bool window_visible();
	void pipeline_load_window_tile();

	void dma_start(uint8_t value);
	void dma_tick(uint8_t cycles);
	bool dma_transferring();

	bool LCDC_BGW_enabled();
	uint16_t LCDC_BGW_data_area();
	uint16_t LCDC_BG_map_area();
	bool LCDC_OBJ_enabled();
	uint8_t LCDC_OBJ_height();
	bool LCDC_WINDOW_enabled();
	uint16_t LCDC_WINDOW_map_area();
	bool LCDC_LCD_enabled();

	LCD_MODE LCDS_mode();
	void LCDS_mode_set(LCD_MODE mode);
	bool LCDS_LYC();
	void LCDS_LYC_set(bool flag);
	bool LCDS_STAT_int(uint8_t value);

	void update_palettes(uint8_t value, uint8_t pal);
	uint8_t LCD_read(uint16_t address);
	void LCD_write(uint16_t address, uint8_t value);
};