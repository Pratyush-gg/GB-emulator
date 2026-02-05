#include "../include/mmu.hpp"
#include "../include/gb_utils.hpp"
#include "../include/ppu.hpp"
#include "../include/joypad.hpp"

#include <iostream>

uint8_t MMU::read_data(const uint16_t address) const {
    if (address < CART_SEG1_OFFSET + CART_SEG1_SIZE) {
        return cartridge->cart_read(address);
    }
    else if (address < VRAM_OFFSET + VRAM_SIZE) {
        return ppu->read_vram(address);
    }
    else if (address < CART_SEG2_OFFSET + CART_SEG2_SIZE) {
        return cartridge->cart_read(address);
    }
    else if (address < WRAM_OFFSET + WRAM_SIZE) {
        const uint16_t offset = address - WRAM_OFFSET;
        if (offset >= WRAM_SIZE) {
            std::cerr << "WRAM read out of bounds: " << std::hex << address << std::endl;
            return 0xFF; // or throw an exception
        }
        return wram[offset];
    }
    else if (address < ERAM_OFFSET + ERAM_SIZE) {
        // const uint16_t offset = address - ERAM_OFFSET;
        // if (offset >= ERAM_SIZE) {
        //     std::cerr << "WRAM read out of bounds: " << std::hex << address << std::endl;
        //     return 0xFF; // or throw an exception
        // }
        // return wram[offset];
        return 0;
    }
    else if (address < OAM_OFFSET + OAM_SIZE) {
        if (ppu->dma_transferring()) {
            return 0xFF;
        }
        return ppu->read_oam(address);
    }
    else if (address < FORBIDDEN_OFFSET + FORBIDDEN_SIZE) {
        return 0;
    }
    else if (address < 0xFF80) {
        if (address == 0xFF00) return joypad->joypad_get_output();
        if (address == 0xFF01) return serial_data[0];
        if (address == 0xFF02) return serial_data[1];
        if (address == 0xFF0F) return this->interrupt->IF;

        if (address >= TIMER_OFFSET && address <= TIMER_END)
            return timer->readAddr(address);

        if (address >= PPO_IO_OFFSET && address <= PPO_IO_END) {
            return ppu->LCD_read(address);
        }

        // TODO : add APU.

        if (address >= 0xFF10 && address <= 0xFF3F) {
            // return apu->readAddr(address);
            return 0xFF;
        }
    }
    if (address < HRAM_OFFSET + HRAM_SIZE) {
        const uint16_t offset = address - HRAM_OFFSET;
        return hram[offset];
    }
    if (address == 0xFFFF) {
        return this->interrupt->IE;
    }
    return -1;
}

void MMU::write_data(uint16_t address, uint8_t value) {
    if (address < CART_SEG1_OFFSET + CART_SEG1_SIZE) {
        cartridge->cart_write(address, value);
        return;
    }

    else if (address >= VRAM_OFFSET && address < VRAM_OFFSET + VRAM_SIZE) {
        ppu->write_vram(address, value);
        return;
    }

    else if (address >= CART_SEG2_OFFSET && address < CART_SEG2_OFFSET + CART_SEG2_SIZE) {
        cartridge->cart_write(address, value);
        return;
    }

    else if (address >= WRAM_OFFSET && address < WRAM_OFFSET + WRAM_SIZE) {
        const uint16_t offset = address - WRAM_OFFSET;
        if (offset >= WRAM_SIZE) {
            std::cerr << "WRAM write out of bounds: " << std::hex << address << std::endl;
            return;
        }
        wram[offset] = value;
        return;
    }

    else if (address >= ERAM_OFFSET && address < ERAM_OFFSET + ERAM_SIZE) {
        // const uint16_t offset = address - ERAM_OFFSET;
        // if (offset >= WRAM_SIZE) {
        //     std::cerr << "Echo RAM write out of bounds: " << std::hex << address << std::endl;
        //     return;
        // }
        // wram[offset] = value;
        return;
    }

    else if (address >= OAM_OFFSET && address < OAM_OFFSET + OAM_SIZE) {
        if (ppu->dma_transferring()) {
            return;
        }
        ppu->write_oam(address, value);
        return;
    }

    else if (address >= 0xFEA0 && address < 0xFF00) {
        return;
    }

    else if (address >= 0xFF00 && address < 0xFF80) {
        if (address == 0xFF00) {
            joypad->joypad_set_select(value);
            return;
        }

        if (address == 0xFF01) {
            serial_data[0] = value;
            return;
        }
        if (address == 0xFF02) {
            serial_data[1] = value;
            return;
        }

        if (address == 0xFF0F) {
            this->interrupt->IF = value;
            return;
        }

        if (address >= TIMER_OFFSET && address <= TIMER_END) {
            timer->writeAddr(address, value);
            return;
        }

        if (address >= PPO_IO_OFFSET && address <= PPO_IO_END) {
            ppu->LCD_write(address, value);
            return;
        }

        if (address >= 0xFF10 && address <= 0xFF3F) {
            // apu->writeAddr(address, value);
            return;
        }

        // TODO: Add APU (0xFF10–0xFF3F)
        // std::cerr << "Write to unusable memory: " << std::hex << address << std::endl;
        return;
    }

    else if (address >= HRAM_OFFSET && address < HRAM_OFFSET + HRAM_SIZE) {
        const uint16_t offset = address - HRAM_OFFSET;
        if (offset >= HRAM_SIZE) {
            std::cerr << "HRAM write out of bounds: " << std::hex << address << std::endl;
            return;
        }
        hram[offset] = value;
        return;
    }

    else if (address == 0xFFFF) {
        this->interrupt->IE = value;
        return;
    }

    // Invalid address fallback
    std::cerr << "Invalid memory write at: " << std::hex << address << " value: " << std::hex << static_cast<int>(value) << std::endl;
}


uint16_t MMU::read_data16(uint16_t address) const {
    const uint16_t low = read_data(address);
    const uint16_t high = read_data(address + 1);
    return low | (high << 8);
}

void MMU::write_data16(uint16_t address, uint16_t value) {
    write_data(address + 1, (value >> 8) & 0xFF);
    write_data(address, value & 0xFF);
}