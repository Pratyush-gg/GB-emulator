#include "../../include/mmu.hpp"

uint8_t MMU::read_data(uint16_t address) {
    if (address < 0x8000) {
        // Read from ROM
        return cartridge->cart_read(address);
    }
    return 0;
}