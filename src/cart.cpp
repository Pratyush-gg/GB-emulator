#include "../include/cart.hpp"

#include <fstream>
#include <cstdint>
#include <ios>
#include <iostream>
#include <fstream>
#include <cstring>
#include <unordered_map>

Cartridge::Cartridge(const std::string &filename) {
    this->filename = filename;
    std::ifstream f1(filename, std::ios::binary);

    if (!f1.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }

    std::cout << "Loading cartridge: " << filename << std::endl;

    constexpr size_t HEADER_OFFSET = 0x100;

    f1.seekg(0, std::ios::end);
    this->rom_size = f1.tellg();
    this->rom_data.resize(this->rom_size);

    f1.seekg(0, std::ios::beg);

    if (this->rom_size < HEADER_OFFSET + sizeof(Header)) {
        std::cerr << "Error: File too small to contain header " << filename << std::endl;
        exit(1);
    }

    f1.read(reinterpret_cast<char*>(this->rom_data.data()), this->rom_size);
    f1.close();

    std::memcpy(&this->cart_header, this->rom_data.data() + HEADER_OFFSET, sizeof(Header));
    this->cart_header.title[15] = '\0';

    this->battery = cart_battery();
    this->needs_save = false;

    std::cout << "Cartridge loaded successfully." << std::endl;

    cart_setup_banking();

    uint16_t calculated_checksum = 0;
    for (uint16_t i = 0x0134; i <= 0x014C; ++i) {
        calculated_checksum  = calculated_checksum - this->rom_data[i] - 1;
    }
    calculated_checksum &= 0xFF;
    if (calculated_checksum == this->cart_header.check_sum) {
        std::cout << "Checksum matches." << std::endl;
    } else {
        std::cerr << "Warning: Checksum does not match!" << std::endl;
    }
    std::cout << "ROM first few bytes: ";
    for (int i = 0; i < 16; ++i) {
        std::printf("%02X ", this->rom_data[i]);
    }
    std::cout << std::endl;

    if (this->battery) {
        cart_battery_load();
    }

    print_cart_info();
}

template<typename T> // template to accommodate both uint8_t and uint16_t
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

void Cartridge::print_cart_info() const {
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

    std::cout << "ROM version: 0x" << std::hex << +this->cart_header.mask_rom_version << std::dec << std::endl << std::endl;
}

uint8_t Cartridge::cart_read(const uint16_t address) const {
    if (!cart_mbc1() || address < 0x4000) {
        return this->rom_data[address];
    }

    if ((address & 0xE000) == 0xA000) {
        if (!this->ram_enabled) {
            return 0xFF;
        }
        if (!this->ram_bank) {
            return 0xFF;
        }
        return this->ram_bank[address - 0xA000];
    }
    return this->rom_bank_x[address - 0x4000];
}

bool Cartridge::cart_needs_save() const {
    return this->needs_save;
}

bool Cartridge::cart_mbc1() const {
    return ((this->cart_header.cart_type >= 0x01 && this->cart_header.cart_type <= 0x03));
}

bool Cartridge::cart_battery() const {
    return (this->cart_header.cart_type == 0x03);
}

void Cartridge::cart_setup_banking() {
    for (int i = 0; i < 16; ++i) {
        this->ram_banks[i] = 0;

        if ((this->cart_header.ram_size == 2 && i == 0) || (this->cart_header.ram_size == 3 && i < 4) || (this->cart_header.ram_size == 4 && i < 16) || (this->cart_header.ram_size == 5 && i < 8)) {
            this->ram_banks[i] = new uint8_t[0x2000];
            std::memset(this->ram_banks[i], 0, 0x2000);
        }
    }
    this->ram_bank = this->ram_banks[0];
    this->rom_bank_x = this->rom_data.data() + 0x4000;
}

void Cartridge::cart_battery_load() {
    std::string fn = this->filename + ".battery";
    std::ifstream file(fn, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open battery file for reading: " << fn << std::endl;
        return;
    }
    file.read(reinterpret_cast<char*>(this->ram_bank), 0x2000);
    file.close();
}

void Cartridge::cart_battery_save() {
    std::string fn = this->filename + ".battery";
    std::ofstream file(fn, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open battery file for writing: " << fn << std::endl;
        return;
    }
    file.write(reinterpret_cast<const char*>(this->ram_bank), 0x2000);
    file.close();
}

void Cartridge::cart_write(uint16_t address, uint8_t value) {
    if (!cart_mbc1()) {
        return;
    }

    if (address < 0x2000) {
        this->ram_enabled = ((value & 0x0F) == 0x0A);
        return;
    }

    if ((address & 0xE000) == 0x2000) {
        if (value == 0) {
            value = 1;
        }
        value &= 0b11111;

        this->rom_bank_value = value;
        this->rom_bank_x = this->rom_data.data() + (0x4000 * this->rom_bank_value);
    }

    if ((address & 0xE000) == 0x4000) {
        this->ram_bank_value = value & 0b1111;
        if (this->ram_banking) {
            if (cart_needs_save()) {
                this->needs_save = true;
            }
            this->ram_bank = this->ram_banks[this->ram_bank_value];
        }
    }

    if ((address & 0xE000) == 0x6000) {
        this->banking_mode = value & 1;

        this->ram_banking = this->banking_mode;

        if (this->ram_banking) {
            if (cart_needs_save()) {
                this->needs_save = true;
            }
            this->ram_bank = this->ram_banks[this->ram_bank_value];
        }
    }

    if ((address & 0xE000) == 0xA000) {
        if (!this->ram_enabled) {
            return;
        }
        if (!this->ram_bank) {
            return;
        }
        this->ram_bank[address - 0xA000] = value;

        if (this->battery) {
            this->needs_save = true;
        }
    }
}