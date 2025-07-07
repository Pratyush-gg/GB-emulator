#include "../include/cart.hpp"

#include <fstream>
#include <cstdint>
#include <iostream>
#include <cstring>

bool Cartridge::cart_load(const std::string filename) {
    this->filename = filename;
    std::ifstream f1(filename, std::ios::binary);

    if (!f1.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::cout << "Loading cartridge: " << filename << std::endl;

    constexpr size_t HEADER_OFFSET = 0x100;

    f1.seekg(0, std::ios::end);
    this->rom_size = f1.tellg();
    this->rom_data.reserve(this->rom_size);

    f1.seekg(0, std::ios::beg);

    if (this->rom_size < HEADER_OFFSET + sizeof(Header)) {
        std::cerr << "Error: File too small to contain header " << filename << std::endl;
        return false;
    }

    f1.read(reinterpret_cast<char*>(this->rom_data.data()), this->rom_size);
    f1.close();

    std::memcpy(&this->cart_header, this->rom_data.data() + HEADER_OFFSET, sizeof(cart_header));
    this->cart_header.title[15] = '\0';

    std::cout << "Cartridge loaded successfully." << std::endl;

    uint16_t calculated_checksum = 0;
    for (uint16_t i = 0x0134; i < 0x014C; ++i) {
        calculated_checksum -= this->rom_data[i] - 1;
    }

    if (calculated_checksum & 0xFF == this->cart_header.check_sum) {
        std::cout << "Checksum matches." << std::endl;
    } else {
        std::cerr << "Warning: Checksum does not match!" << std::endl;
    }
    return true;
}

void Cartridge::print_cart_info() {
    // TODO : find another way to figure out coz both those pointers will not be null now
    // if (!ctx.cart_header || !ctx.rom_data) {
    //     cout << "Error: No cartridge header loaded." << endl;
    //     return;
    // }
    std::cout << "Cartridge Information:" << std::endl;
    std::cout << "File: " << this->filename << std::endl;
    std::cout << "Title: " << this->cart_header.title << std::endl;

    std::cout << "Cartridge Type: 0x" << std::hex << +this->cart_header.cart_type << " (";
    auto it = cart_type_lookup.find(this->cart_header.cart_type);
    if (it != cart_type_lookup.end()) {
        std::cout << it->second << ")" << std::dec << std::endl;
    } else {
        std::cout << "Unknown)" << std::dec << std::endl;
    }

    std::cout << "Original ROM Size: " << this->rom_size << " bytes" << std::endl;

    std::cout << "ROM Size: 0x" << std::hex << +this->cart_header.rom_size << " (";
    auto it = rom_size_lookup.find(this->cart_header.rom_size);
    if (it != rom_size_lookup.end()) {
        std::cout << it->second << ")" << std::endl;
    } else {
        std::cout << "Unknown)" << std::endl;
    }

    std::cout << "RAM Size: 0x" << std::hex << +this->cart_header.ram_size << " (";
    auto it = ram_size_lookup.find(this->cart_header.ram_size);
    if (it != ram_size_lookup.end()) {
        std::cout << it->second << ")" << std::endl;
    } else {
        std::cout << "Unknown)" << std::endl;
    }

    std::cout << "License Code: 0x" << std::hex << this->cart_header.license_code;
    if (this->cart_header.license_code == 0x00) {
        std::cout << " (None)" << std::dec << std::endl;
    }
    else {
        auto it = license_code_lookup.find(this->cart_header.license_code);
        if (it != license_code_lookup.end()) {
            std::cout << " (" << it->second << ")" << std::dec << std::endl;
        } else {
            std::cout << " (Unknown)" << std::dec << std::endl;
        }
    }

    std::cout << "ROM version: 0x" << std::hex << +this->cart_header.mask_rom_version << std::dec << std::endl;
}

uint8_t Cartridge::cart_read(uint16_t address) {
    return this->rom_data[address];
}

void Cartridge::cart_write(uint16_t address, uint8_t value) {
    // nothing
}
