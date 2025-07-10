#include "../include/cart.hpp"

#include <fstream>
#include <cstdint>
#include <ios>
#include <iostream>
#include <cstring>
#include <unordered_map>

bool Cartridge::cart_load(const std::string &filename) {
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

    if ((calculated_checksum & 0xFF) == this->cart_header.check_sum) {
        std::cout << "Checksum matches." << std::endl;
    } else {
        std::cerr << "Warning: Checksum does not match!" << std::endl;
    }
    return true;
}

template<typename T> // template to accomodate both uint8_t and uint16_t
void print_info(const std::string&& label, T key, 
        const std::unordered_map<T, std::string> &lookup_table, bool show_key = true) {

    // display required label
    std::cout << label << ": ";

    if (show_key) {
        std::cout << " 0x" << std::hex << static_cast<int>(key) << std::dec << " ";
    }

    std::cout << "(";
    if (auto it = lookup_table.find(key); it != lookup_table.end()) { // cool modern if statement
        std::cout << it->second;
    } else {
        std::cout << "Unknown";
    }
    std::cout << ")" << std::endl;
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

    print_info("Cartridge Type", static_cast<uint16_t>(this->cart_header.cart_type), cart_type_lookup);

    std::cout << "Original ROM Size: " << this->rom_size << " bytes" << std::endl;
    print_info("ROM Size", this->cart_header.rom_size, rom_size_lookup);

    print_info("RAM Size", this->cart_header.ram_size, ram_size_lookup);

    print_info("License Code", static_cast<uint16_t>(this->cart_header.license_code), license_code_lookup);

    std::cout << "ROM version: 0x" << std::hex << +this->cart_header.mask_rom_version << std::dec << std::endl;
}

uint8_t Cartridge::cart_read(uint16_t address) {
    return this->rom_data[address];
}

void Cartridge::cart_write(uint16_t address, uint8_t value) {
    // nothing
}
