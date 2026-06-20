#include "../include/cart.hpp"

#include <fstream>
#include <cstdint>
#include <ios>
#include <iostream>
#include <cstring>
#include <unordered_map>
#include <ctime>

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
    if (address < 0x4000) {
        if (cart_mbc1() && this->banking_mode == 1) {
            size_t total_rom_banks = this->rom_data.size() / 0x4000;
            if (total_rom_banks == 0) total_rom_banks = 1;
            uint8_t bank_0 = (this->rom_bank_high << 5) % total_rom_banks;
            return this->rom_data[(bank_0 * 0x4000) + address];
        } else {
            return this->rom_data[address];
        }
    }

    if (address < 0x8000) {
        if (!cart_mbc1() && !cart_mbc2() && !cart_mbc3() && !cart_mbc5()) {
            return this->rom_data[address];
        }
        return this->rom_bank_x[address - 0x4000];
    }

    if ((address & 0xE000) == 0xA000) {
        if (cart_mbc1() || cart_mbc5()) {
            if (!this->ram_enabled || !this->ram_bank) {
                return 0xFF;
            }
            return this->ram_bank[address - 0xA000];
        } else if (cart_mbc2()) {
            if (!this->ram_enabled) {
                return 0xFF;
            }
            uint16_t offset = (address - 0xA000) & 0x01FF;
            return 0xF0 | (this->mbc2_ram[offset] & 0x0F);
        } else if (cart_mbc3()) {
            if (!this->ram_enabled) {
                return 0xFF;
            }
            if (this->ram_bank_value <= 0x03) {
                if (!this->ram_bank) {
                    return 0xFF;
                }
                return this->ram_bank[address - 0xA000];
            } else if (this->ram_bank_value >= 0x08 && this->ram_bank_value <= 0x0C) {
                const_cast<Cartridge*>(this)->update_rtc();
                return this->latched_rtc_registers[this->ram_bank_value - 0x08];
            }
            return 0xFF;
        }
        return 0xFF;
    }

    return 0xFF;
}

bool Cartridge::cart_needs_save() const {
    return this->needs_save;
}

bool Cartridge::cart_mbc1() const {
    return (this->cart_header.cart_type >= 0x01 && this->cart_header.cart_type <= 0x03);
}

bool Cartridge::cart_mbc2() const {
    return (this->cart_header.cart_type == 0x05 || this->cart_header.cart_type == 0x06);
}

bool Cartridge::cart_mbc3() const {
    return (this->cart_header.cart_type >= 0x0F && this->cart_header.cart_type <= 0x13);
}

bool Cartridge::cart_mbc5() const {
    return (this->cart_header.cart_type >= 0x19 && this->cart_header.cart_type <= 0x1E);
}

bool Cartridge::cart_battery() const {
    return (this->cart_header.cart_type == 0x03 || 
            this->cart_header.cart_type == 0x06 ||
            this->cart_header.cart_type == 0x0F || 
            this->cart_header.cart_type == 0x10 || 
            this->cart_header.cart_type == 0x13 ||
            this->cart_header.cart_type == 0x1B ||
            this->cart_header.cart_type == 0x1E);
}

void Cartridge::cart_setup_banking() {
    for (int i = 0; i < 16; ++i) {
        this->ram_banks[i] = nullptr;

        if ((this->cart_header.ram_size == 2 && i == 0) || 
            (this->cart_header.ram_size == 3 && i < 4) || 
            (this->cart_header.ram_size == 4 && i < 16) || 
            (this->cart_header.ram_size == 5 && i < 8)) {
            this->ram_banks[i] = new uint8_t[0x2000];
            std::memset(this->ram_banks[i], 0, 0x2000);
        }
    }
    this->ram_bank = this->ram_banks[0];
    this->rom_bank_x = this->rom_data.data() + 0x4000;
    this->rom_bank_low = 1;
    this->rom_bank_high = 0;
    this->rom_bank_value = 1;
    this->ram_bank_value = 0;
    this->banking_mode = 0;
    this->ram_banking = false;

    std::memset(this->mbc2_ram, 0, sizeof(this->mbc2_ram));
    std::memset(this->rtc_registers, 0, sizeof(this->rtc_registers));
    std::memset(this->latched_rtc_registers, 0, sizeof(this->latched_rtc_registers));
    this->clock_latch_state = false;
    this->last_rtc_update_time = static_cast<uint32_t>(std::time(nullptr));
}

void Cartridge::update_rtc() {
    uint32_t current_time = static_cast<uint32_t>(std::time(nullptr));
    if (current_time > this->last_rtc_update_time) {
        uint32_t elapsed = current_time - this->last_rtc_update_time;
        this->add_rtc_seconds(elapsed);
        this->last_rtc_update_time = current_time;
    } else if (current_time < this->last_rtc_update_time) {
        this->last_rtc_update_time = current_time;
    }
}

void Cartridge::add_rtc_seconds(uint64_t seconds) {
    if (this->rtc_registers[4] & 0x40) {
        return;
    }

    uint64_t s = this->rtc_registers[0] + seconds;
    uint64_t m = this->rtc_registers[1] + (s / 60);
    s %= 60;

    uint64_t h = this->rtc_registers[2] + (m / 60);
    m %= 60;

    uint64_t days = ((this->rtc_registers[4] & 1) << 8) | this->rtc_registers[3];
    days += (h / 24);
    h %= 24;

    this->rtc_registers[0] = static_cast<uint8_t>(s);
    this->rtc_registers[1] = static_cast<uint8_t>(m);
    this->rtc_registers[2] = static_cast<uint8_t>(h);
    this->rtc_registers[3] = static_cast<uint8_t>(days & 0xFF);

    uint8_t dh = this->rtc_registers[4] & 0xFE;
    dh |= ((days >> 8) & 1);

    if (days >= 512) {
        dh |= 0x80;
    }
    this->rtc_registers[4] = dh;
}

void Cartridge::update_banks() {
    size_t total_rom_banks = this->rom_data.size() / 0x4000;
    if (total_rom_banks == 0) total_rom_banks = 1;

    if (cart_mbc1()) {
        uint8_t bank_x = (this->rom_bank_high << 5) | this->rom_bank_low;
        bank_x %= total_rom_banks;
        this->rom_bank_value = bank_x;
        this->rom_bank_x = this->rom_data.data() + (0x4000 * bank_x);

        if (this->banking_mode == 0) {
            this->ram_bank = this->ram_banks[0];
        } else {
            uint8_t ram_bank_mask = 0;
            if (this->cart_header.ram_size == 3) ram_bank_mask = 3;
            else if (this->cart_header.ram_size == 4) ram_bank_mask = 15;
            else if (this->cart_header.ram_size == 5) ram_bank_mask = 7;

            uint8_t bank_ram = this->ram_bank_value & ram_bank_mask;
            this->ram_bank = this->ram_banks[bank_ram];
        }
    } else if (cart_mbc2()) {
        uint8_t bank_x = this->rom_bank_value & 0x0F;
        bank_x %= total_rom_banks;
        this->rom_bank_x = this->rom_data.data() + (0x4000 * bank_x);
        this->ram_bank = nullptr;
    } else if (cart_mbc3()) {
        uint8_t bank_x = this->rom_bank_value & 0x7F;
        bank_x %= total_rom_banks;
        this->rom_bank_x = this->rom_data.data() + (0x4000 * bank_x);

        if (this->ram_bank_value <= 0x03) {
            uint8_t ram_bank_mask = 0;
            if (this->cart_header.ram_size == 3) ram_bank_mask = 3;
            else if (this->cart_header.ram_size == 4) ram_bank_mask = 15;
            else if (this->cart_header.ram_size == 5) ram_bank_mask = 7;

            uint8_t bank_ram = this->ram_bank_value & ram_bank_mask;
            this->ram_bank = this->ram_banks[bank_ram];
        } else {
            this->ram_bank = nullptr;
        }
    } else if (cart_mbc5()) {
        uint16_t bank_x = this->rom_bank_value & 0x1FF;
        bank_x %= total_rom_banks;
        this->rom_bank_x = this->rom_data.data() + (0x4000 * bank_x);

        uint8_t ram_bank_mask = 0;
        if (this->cart_header.ram_size == 3) ram_bank_mask = 3;
        else if (this->cart_header.ram_size == 4) ram_bank_mask = 15;
        else if (this->cart_header.ram_size == 5) ram_bank_mask = 7;

        uint8_t bank_ram = this->ram_bank_value & ram_bank_mask;
        this->ram_bank = this->ram_banks[bank_ram];
    }
}

void Cartridge::cart_battery_load() {
    std::string fn = this->filename + ".battery";
    std::ifstream file(fn, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open battery file for reading: " << fn << std::endl;
        return;
    }

    if (cart_mbc2()) {
        file.read(reinterpret_cast<char*>(this->mbc2_ram), 512);
    } else {
        size_t total_banks = 0;
        if (this->cart_header.ram_size == 2) total_banks = 1;
        else if (this->cart_header.ram_size == 3) total_banks = 4;
        else if (this->cart_header.ram_size == 4) total_banks = 16;
        else if (this->cart_header.ram_size == 5) total_banks = 8;

        for (size_t i = 0; i < total_banks; i++) {
            if (this->ram_banks[i]) {
                file.read(reinterpret_cast<char*>(this->ram_banks[i]), 0x2000);
            }
        }
    }

    if (cart_mbc3()) {
        uint64_t saved_time = 0;
        file.read(reinterpret_cast<char*>(this->rtc_registers), 5);
        file.read(reinterpret_cast<char*>(this->latched_rtc_registers), 5);
        if (file.read(reinterpret_cast<char*>(&saved_time), 8)) {
            uint64_t current_time = static_cast<uint64_t>(std::time(nullptr));
            if (current_time > saved_time) {
                uint64_t elapsed = current_time - saved_time;
                this->add_rtc_seconds(elapsed);
            }
            this->last_rtc_update_time = static_cast<uint32_t>(current_time);
        }
    }
    file.close();
}

void Cartridge::cart_battery_save() {
    std::string fn = this->filename + ".battery";
    std::ofstream file(fn, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open battery file for writing: " << fn << std::endl;
        return;
    }

    if (cart_mbc2()) {
        file.write(reinterpret_cast<const char*>(this->mbc2_ram), 512);
    } else {
        size_t total_banks = 0;
        if (this->cart_header.ram_size == 2) total_banks = 1;
        else if (this->cart_header.ram_size == 3) total_banks = 4;
        else if (this->cart_header.ram_size == 4) total_banks = 16;
        else if (this->cart_header.ram_size == 5) total_banks = 8;

        for (size_t i = 0; i < total_banks; i++) {
            if (this->ram_banks[i]) {
                file.write(reinterpret_cast<const char*>(this->ram_banks[i]), 0x2000);
            }
        }
    }

    if (cart_mbc3()) {
        uint64_t current_time = static_cast<uint64_t>(std::time(nullptr));
        file.write(reinterpret_cast<const char*>(this->rtc_registers), 5);
        file.write(reinterpret_cast<const char*>(this->latched_rtc_registers), 5);
        file.write(reinterpret_cast<const char*>(&current_time), 8);
    }
    file.close();
    this->needs_save = false;
}

void Cartridge::cart_write(uint16_t address, uint8_t value) {
    if (!cart_mbc1() && !cart_mbc2() && !cart_mbc3() && !cart_mbc5()) {
        return;
    }

    if (address < 0x2000) {
        if (cart_mbc2()) {
            if (!(address & 0x0100)) {
                this->ram_enabled = ((value & 0x0F) == 0x0A);
            }
        } else {
            this->ram_enabled = ((value & 0x0F) == 0x0A);
        }
        return;
    }

    if (address < 0x4000) {
        if (cart_mbc1()) {
            uint8_t low_5_bits = value & 0x1F;
            if (low_5_bits == 0) {
                low_5_bits = 1;
            }
            this->rom_bank_low = low_5_bits;
        } else if (cart_mbc2()) {
            if (address & 0x0100) {
                uint8_t bank = value & 0x0F;
                if (bank == 0) {
                    bank = 1;
                }
                this->rom_bank_value = bank;
            }
        } else if (cart_mbc3()) {
            uint8_t bank = value & 0x7F;
            if (bank == 0) {
                bank = 1;
            }
            this->rom_bank_value = bank;
        } else if (cart_mbc5()) {
            if (address < 0x3000) {
                this->rom_bank_value = (this->rom_bank_value & 0x0100) | value;
            } else {
                this->rom_bank_value = (this->rom_bank_value & 0x00FF) | ((value & 1) << 8);
            }
        }
        this->update_banks();
        return;
    }

    if (address < 0x6000) {
        if (cart_mbc1()) {
            this->rom_bank_high = value & 0x03;
            this->ram_bank_value = value & 0x03;
        } else if (cart_mbc3()) {
            this->ram_bank_value = value;
        } else if (cart_mbc5()) {
            this->ram_bank_value = value & 0x0F;
        }
        this->update_banks();
        return;
    }

    if (address < 0x8000) {
        if (cart_mbc1()) {
            this->banking_mode = value & 1;
            this->ram_banking = this->banking_mode;
            if (cart_needs_save()) {
                this->needs_save = true;
            }
            this->update_banks();
        } else if (cart_mbc3()) {
            if (this->clock_latch_state == false && value == 1) {
                this->update_rtc();
                std::memcpy(this->latched_rtc_registers, this->rtc_registers, 5);
            }
            this->clock_latch_state = (value == 1);
        }
        return;
    }

    if ((address & 0xE000) == 0xA000) {
        if (!this->ram_enabled) {
            return;
        }
        if (cart_mbc1() || cart_mbc5()) {
            if (!this->ram_bank) {
                return;
            }
            this->ram_bank[address - 0xA000] = value;
            if (this->battery) {
                this->needs_save = true;
            }
        } else if (cart_mbc2()) {
            uint16_t offset = (address - 0xA000) & 0x01FF;
            this->mbc2_ram[offset] = value & 0x0F;
            if (this->battery) {
                this->needs_save = true;
            }
        } else if (cart_mbc3()) {
            if (this->ram_bank_value <= 0x03) {
                if (!this->ram_bank) {
                    return;
                }
                this->ram_bank[address - 0xA000] = value;
                if (this->battery) {
                    this->needs_save = true;
                }
            } else if (this->ram_bank_value >= 0x08 && this->ram_bank_value <= 0x0C) {
                this->update_rtc();
                this->rtc_registers[this->ram_bank_value - 0x08] = value;
                this->last_rtc_update_time = static_cast<uint32_t>(std::time(nullptr));
            }
        }
        return;
    }
}