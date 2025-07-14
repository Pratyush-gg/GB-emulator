#include "../../include/mmu.hpp"

#include <iostream>

uint8_t MMU::read_data(uint16_t address) {
    if (address < 0x8000) {
        return cartridge->cart_read(address);
    }
    return 0;
}

void MMU::write_data(uint16_t address, uint8_t value) {
    if (address < 0x8000) {
        // cart write
        return;
    }
    std::cerr << "Error: Attempt to write to ROM address: " << std::hex << address << std::dec << std::endl;
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