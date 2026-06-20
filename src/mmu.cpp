#include "../include/mmu.hpp"
#include "../include/gb_utils.hpp"
#include "../include/ppu.hpp"
#include "../include/joypad.hpp"
#include "../include/interrupt.hpp"
#include "../include/apu.hpp"
#include "../include/cart.hpp"

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
        return read_data(address - 0x2000);
    }
    else if (address >= OAM_OFFSET && address < 0xFF00) {
        if (ppu->dma_transferring()) {
            return 0xFF;
        }
        ppu->trigger_oam_bug(false);
        if (address < OAM_OFFSET + OAM_SIZE) {
            return ppu->read_oam(address);
        }
        return 0xFF;
    }
    else if (address < 0xFF80) {
        if (address == 0xFF00) return joypad->joypad_get_output();
        if (address == 0xFF01) return serial_data[0];
        if (address == 0xFF02) return serial_data[1];
        if (address == 0xFF0F) return this->interrupt->IF | 0xE0;

        if (address >= TIMER_OFFSET && address <= TIMER_END)
            return timer->readAddr(address);

        if (address >= PPO_IO_OFFSET && address <= PPO_IO_END) {
            return ppu->LCD_read(address);
        }

        if (address >= 0xFF10 && address <= 0xFF3F) {
			return apu->readMem(address);
            return 0xFF;
        }
    }
    if (address < HRAM_OFFSET + HRAM_SIZE) {
        const uint16_t offset = address - HRAM_OFFSET;
        return hram[offset];
    }
    if (address == 0xFFFF) {
        return this->interrupt->IE | 0xE0;
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
        write_data(address - 0x2000, value);
        return;
    }

    else if (address >= OAM_OFFSET && address < 0xFF00) {
        if (ppu->dma_transferring()) {
            return;
        }
        ppu->trigger_oam_bug(true);
        if (address < OAM_OFFSET + OAM_SIZE) {
            ppu->write_oam(address, value);
        }
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
            this->interrupt->IF = value | 0xE0;
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
			apu->writeMem(address, value);
            return;
        }

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
        this->interrupt->IE = value | 0xE0;
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

void MMU::trigger_oam_bug(bool is_write) {
    ppu->trigger_oam_bug(is_write);
}