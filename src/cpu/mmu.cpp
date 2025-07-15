#include "../../include/mmu.hpp"
#include "../../include/gb_utils.hpp"

#include <iostream>

uint8_t MMU::read_data(uint16_t address) {
    if (address < 0x8000) {
        return cartridge->cart_read(address);
    }
    else if (address < 0xA000) {
        //TODO: Implement VRAM read
        std::cerr << "Error: Attempt to read from VRAM address: " << std::hex << address << std::dec << std::endl;
        not_implemented("read_data VRAM");
    }
    else if (address < 0xC000) {
        return cartridge->cart_read(address);
    }
    else if (address < 0xE000) {
        // TODO: Implement WRAM read
        not_implemented("read_data WRAM");
    }
    else if (address < 0xFE00) {
        return 0;
    }
    else if (address < 0xFEA0) {
        // TODO: Implement OAM read
        not_implemented("read_data OAM");
    }
    else if (address < 0xFF00) {
        return 0;
    }
    else if (address < 0xFF80) {
        // TODO: Implement I/O registers read
        not_implemented("read_data I/O registers");
    }
    else if (address == 0xFFFF) {
        //TODO: Implement Interrupt Enable register read
        not_implemented("read_data Interrupt Enable register");
    }
    else {
        //TODO: Implement HRAM read
        not_implemented("read_data HRAM");
    }
}

void MMU::write_data(uint16_t address, uint8_t value) {
    if (address < 0x8000) {
        //TODO: Implement cartridge write
        not_implemented("cart_write");
    }
    else if (address < 0xA000) {
        //TODO: Implement VRAM write
        not_implemented("write_data VRAM");
    }
    else if (address < 0xC000) {
        //TODO: Implement cartridge write
        not_implemented("cart_write");
    }
    else if (address < 0xE000) {
        //TODO: Implement WRAM write
        not_implemented("write_data WRAM");
    }
    else if (address < 0xFE00) {
        return;
    }
    else if (address < 0xFEA0) {
        // TODO: Implement OAM write
        not_implemented("write_data OAM");
    }
    else if (address < 0xFF00) {
        return;
    }
    else if (address < 0xFF80) {
        // TODO: Implement I/O registers write
        not_implemented("write_data I/O registers");
    }
    else if (address == 0xFFFF) {
        //TODO: Implement Interrupt Enable register write
        not_implemented("write_data Interrupt Enable register");
    }
    else {
        //TODO: Implement HRAM write
        not_implemented("write_data HRAM");
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