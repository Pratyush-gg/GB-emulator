#include "../../include/mmu.hpp"
#include "../../include/gb_utils.hpp"

#include <iostream>

uint8_t MMU::read_data(uint16_t address) {
    if (address < 0x8000) {
        return cartridge->cart_read(address);
    }
    else if (address < 0xA000) {
        // return ppu->read_vram(address);
    }
    else if (address < 0xC000) {
        return cartridge->cart_read(address);
    }
    else if (address < 0xE000) {
		// if (address < WRAM_OFFSET || address >= WRAM_OFFSET + WRAM_SIZE)
		// 	throw std::out_of_range("WRAM write out of bounds");
		// return wram[address - WRAM_OFFSET];
    }
    else if (address < 0xFE00) {
        return 0;
    }
    else if (address < 0xFEA0) {
        // return ppu->read_oam(address);
        return 0x0;
    }
    else if (address < 0xFF00) {
        return 0;
    }
    else if (address < 0xFF80) {
        return ppu->io_read(address);
    }
    else if (address == 0xFFFF) {
        return ie_register;
    }
    else {
		if (address < HRAM_OFFSET || address >= HRAM_OFFSET + HRAM_SIZE)
			throw std::out_of_range("HRAM write out of bounds");
        return hram[address - HRAM_OFFSET];
    }
}

void MMU::write_data(uint16_t address, uint8_t value) {
    if (address < 0x8000) {
        //TODO: Implement cartridge write
        not_implemented("cart_write");
    }
    else if (address < 0xA000) {
        // ppu->write_vram(address, value);
    }
    else if (address < 0xC000) {
        //TODO: Implement cartridge write
        not_implemented("cart_write");
    }
    else if (address < 0xE000) {
        // if (address < WRAM_OFFSET || address >= WRAM_OFFSET + WRAM_SIZE)
		// 	throw std::out_of_range("WRAM write out of bounds");
		// wram[address - WRAM_OFFSET] = value;
    }
    else if (address < 0xFE00) {
        return;
    }
    else if (address < 0xFEA0) {
		// return ppu->write_oam(address, value);
    }
    else if (address < 0xFF00) {

    }
    else if (address < 0xFF80) {
        ppu->io_write(address, value);
    }
    else if (address == 0xFFFF) {
        ie_register = value;
    }
    else {
		if (address < HRAM_OFFSET || address >= HRAM_OFFSET + HRAM_SIZE)
			throw std::out_of_range("HRAM write out of bounds");
		hram[address - HRAM_OFFSET] = value;
    }
}

uint16_t MMU::read_data16(uint16_t address) {
    uint8_t low = read_data(address);
    uint8_t high = read_data(address + 1);
    return (high << 8) | low;
}

void MMU::write_data16(uint16_t address, uint16_t value) {
    write_data(address + 1, (value >> 8) & 0xFF);
    write_data(address, value & 0xFF);
}