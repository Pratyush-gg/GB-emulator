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
    std::cout << "ROM Size: " << this->rom_size << " bytes" << std::endl;
    std::cout << "Title: " << this->cart_header.title << std::endl;
    // print other stuff...
}

uint8_t Cartridge::cart_read(uint16_t address) {
    return this->rom_data[address];
}

void Cartridge::cart_write(uint16_t address, uint8_t value) {
    // nothing
}
