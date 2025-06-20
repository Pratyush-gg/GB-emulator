#pragma once
#include "gb_utils.hpp"

class cart_header {
        u8 entry_point[4]; // 0100 - 0103
        u8 logo[30]; // 0104 - 0133
        char title[16]; // 0134 - 0143
        u16 license_code; // 0144 - 0145
        u8 sgb_flag; // 0146
        u8 cart_type; // 0147
        u8 rom_size; // 0148
        u8 ram_size; // 0149
        u8 dest_code; // 014A
        u8 old_license_code; // 014B
        u8 mask_rom_version; // 014C
        u8 check_sum; // 014D
        u16 global_check_sum; // 014E - 014F
};
bool cart_load(const char* file);
void print_cart_info();