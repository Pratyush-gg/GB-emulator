#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>

#ifdef _MSC_VER
    #pragma pack(push, 1)
    struct Header {
#elif defined(__GNUC__)
    struct __attribute__((packed)) Header {
#else
    struct Header {
#endif
    uint8_t entry_point[4]; // 0100 - 0103
    uint8_t logo[0x30]; // 0104 - 0133
    char title[16]; // 0134 - 0143
    uint16_t license_code; // 0144 - 0145
    uint8_t sgb_flag; // 0146
    uint8_t cart_type; // 0147
    uint8_t rom_size; // 0148
    uint8_t ram_size; // 0149
    uint8_t dest_code; // 014A
    uint8_t old_license_code; // 014B
    uint8_t mask_rom_version; // 014C
    uint8_t check_sum; // 014D
    uint16_t global_check_sum; // 014E - 014F
};

#ifdef _MSC_VER
    #pragma pack(pop)
#endif

class Cartridge {
public:
    Cartridge(const std::string &filename);

    std::string filename;
    uint32_t rom_size;
    std::vector<uint8_t> rom_data;
    Header cart_header;

    void print_cart_info();

    uint8_t cart_read(uint16_t address);
    // void cart_write(uint16_t address, uint8_t value);
};

const std::unordered_map<uint16_t, std::string> license_code_lookup = {
    {0x00, "None"},
    {0x01, "Nintendo R&D1"},
    {0x08, "Capcom"},
    {0x13, "Electronic Arts"},
    {0x18, "Hudson Soft"},
    {0x19, "B-AI"},
    {0x20, "KSS"},
    {0x22, "Planning Office WADA"},
    {0x24, "PCM Complete"},
    {0x25, "San-X"},
    {0x28, "Kemco"},
    {0x29, "Seta Corporation"},
    {0x30, "Viacom"},
    {0x31, "Nintendo"},
    {0x32, "Bandai"},
    {0x33, "Ocean Software/Acclaim Entertainment"},
    {0x34, "Konami"},
    {0x35, "Hector"},
    {0x37, "Taito"},
    {0x38, "Hudson Soft"},
    {0x39, "Banpresto"},
    {0x41, "Ubisoft"},
    {0x42, "Atlus"},
    {0x44, "Malibu Interactive"},
    {0x46, "Angel"},
    {0x47, "Bullet-Proof Software"},
    {0x49, "IREM"},
    {0x50, "Absolute"},
    {0x51, "Acclaim Entertainment"},
    {0x52, "Activision"},
    {0x53, "Sammy USA Corporation"},
    {0x54, "Konami"},
    {0x55, "Hi Tech Expressions"},
    {0x56, "LJN"},
    {0x57, "Matchbox"},
    {0x58, "Mattel"},
    {0x59, "Milton Bradley Company"},
    {0x60, "Titus Interactive"},
    {0x61, "Virgin Games Ltd."},
    {0x64, "Lucasfilm Games"},
    {0x67, "Ocean Software"},
    {0x69, "EA (Electronic Arts)"},
    {0x70, "Infogrames"},
    {0x71, "Interplay Entertainment"},
    {0x72, "Broderbund"},
    {0x73, "Sculptured Software"},
    {0x75, "The Sales Curve Limited"},
    {0x78, "THQ"},
    {0x79, "Accolade"},
    {0x80, "Misawa Entertainment"},
    {0x83, "lozc"},
    {0x86, "Tokuma Shoten"},
    {0x87, "Tsukuda Original"},
    {0x91, "Chunsoft Co."},
    {0x92, "Video System"},
    {0x93, "Ocean Software/Acclaim Entertainment"},
    {0x95, "Varie"},
    {0x96, "Yonezawa/S'Pal"},
    {0x97, "Kaneko"},
    {0x99, "Pack-In-Video"},
};

const std::unordered_map<uint16_t, std::string> cart_type_lookup = {
    {0x00, "ROM only"},
    {0x01, "MBC1"},
    {0x02, "MBC1+RAM"},
    {0x03, "MBC1+RAM+BATTERY"},
    {0x05, "MBC2"},
    {0x06, "MBC2+BATTERY"},
    {0x08, "ROM+RAM"},
    {0x09, "ROM+RAM+BATTERY"},
    {0x0B, "MMM01"},
    {0x0C, "MMM01+RAM"},
    {0x0D, "MMM01+RAM+BATTERY"},
    {0x0F, "MBC3+TIMER+BATTERY"},
    {0x10, "MBC3+TIMER+RAM+BATTERY"},
    {0x11, "MBC3"},
    {0x12, "MBC3+RAM"},
    {0x13, "MBC3+RAM+BATTERY"},
    {0x19, "MBC5"},
    {0x1A, "MBC5+RAM"},
    {0x1B, "MBC5+RAM+BATTERY"},
    {0x1C, "MBC5+RUMBLE"},
    {0x1D, "MBC5+RUMBLE+RAM"},
    {0x1E, "MBC5+RUMBLE+RAM+BATTERY"},
    {0x20, "MBC6"},
    {0x22, "MBC7+SENSOR+RUMBLE+RAM+BATTERY"},
    {0xFC, "POCKET CAMERA"},
    {0xFD, "BANDAI TAMA5"},
    {0xFE, "HuC-3"},
    {0xFF, "HuC-1+RAM+BATTERY"},
};

const std::unordered_map<uint8_t, std::string> rom_size_lookup = {
    {0x00, "32 KiB"},
    {0x01, "64 KiB"},
    {0x02, "128 KiB"},
    {0x03, "256 KiB"},
    {0x04, "512 KiB"},
    {0x05, "1 MiB"},
    {0x06, "2 MiB"},
    {0x07, "4 MiB"},
    {0x08, "8 MiB"},
    {0x52, "1.1 MiB"},
    {0x53, "1.2 MiB"},
    {0x54, "1.5 MiB"},
};

const std::unordered_map<uint8_t, std::string> ram_size_lookup = {
    {0x00, "None"},
    {0x01, "2 KiB"},
    {0x02, "8 KiB"},
    {0x03, "32 KiB"},
    {0x04, "128 KiB"},
    {0x05, "64 KiB"},
};

const std::unordered_map<uint8_t, std::string> dest_code_lookup = {
    {0x00, "Japan (and possibly overseas)"},
    {0x01, "Overseas Only"}
};

const std::unordered_map<uint8_t, std::string> old_license_code_lookup= {
    {0x00, "None"},
    {0x01, "Nintendo"},
    {0x08, "Capcom"},
    {0x09, "HOT-B"},
    {0x0A, "Jaleco"},
    {0x0B, "Coconuts Japan"},
    {0x0C, "Elite Systems"},
    {0x13, "Electronic Arts"},
    {0x18, "Hudson Soft"},
    {0x19, "ITC Entertainment"},
    {0x1A, "Yanoman"},
    {0x1D, "Japan Clary"},
    {0x1F, "Virgin"},
    {0x24, "PCM Complete"},
    {0x25, "San-X"},
    {0x28, "Kemco"},
    {0x29, "SETA"},
    {0x30, "Infogrames"},
    {0x31, "Nintendo"},
    {0x32, "Bandai"},
    {0x33, "Use New Licensee Code (0144/0145)"},
    {0x34, "Konami"},
    {0x35, "Hector"},
    {0x38, "Capcom"},
    {0x39, "Banpresto"},
    {0x3C, "Entertainment i"},
    {0x3E, "Gremlin"},
    {0x41, "Ubisoft"},
    {0x42, "Atlus"},
    {0x44, "Malibu"},
    {0x46, "Angel"},
    {0x47, "Bullet-Proof"},
    {0x49, "IREM"},
    {0x4A, "Virgin"},
    {0x4D, "Malibu"},
    {0x4F, "U.S. Gold"},
    {0x50, "Absolute"},
    {0x51, "Acclaim"},
    {0x52, "Activision"},
    {0x53, "American Sammy"},
    {0x54, "Konami"},
    {0x55, "Hi Tech"},
    {0x56, "LJN"},
    {0x57, "Matchbox"},
    {0x59, "Milton Bradley"},
    {0x5A, "Mindscape"},
    {0x5B, "Romstar"},
    {0x5C, "Naxat Soft"},
    {0x5D, "Tradewest"},
    {0x60, "Titus"},
    {0x61, "Virgin"},
    {0x67, "Ocean"},
    {0x69, "EA"},
    {0x6E, "Elite"},
    {0x6F, "Electro Brain"},
    {0x70, "Infogrames"},
    {0x71, "Interplay"},
    {0x72, "Broderbund"},
    {0x73, "Sculptured"},
    {0x75, "The Sales Curve"},
    {0x78, "THQ"},
    {0x79, "Accolade"},
    {0x7A, "Triffix Entertainment"},
    {0x7C, "Microprose"},
    {0x7F, "Kemco"},
    {0x80, "Misawa"},
    {0x83, "Lozc"},
    {0x86, "Tokuma Shoten"},
    {0x8B, "Bullet-Proof"},
    {0x8C, "Vic Tokai"},
    {0x8E, "Ape"},
    {0x8F, "I’Max"},
    {0x91, "Chunsoft"},
    {0x92, "Video System"},
    {0x93, "Tsuburava"},
    {0x95, "Varie"},
    {0x96, "Yonezawa/S'Pal"},
    {0x97, "Kaneko"},
    {0x99, "Arc"},
    {0x9A, "Nihon Bussan"},
    {0x9B, "Tecmo"},
    {0x9C, "Imagineer"},
    {0x9D, "Banpresto"},
    {0x9F, "Nova"},
    {0xA1, "Hori Electric"},
    {0xA2, "Bandai"},
    {0xA4, "Konami"},
    {0xA6, "Kawada"},
    {0xA7, "Takara"},
    {0xA9, "Technos Japan"},
    {0xAA, "Broderbund"},
    {0xAC, "Toei Animation"},
    {0xAD, "Toho"},
    {0xAF, "Namco"},
    {0xB0, "Acclaim"},
    {0xB1, "ASCII or Nexoft"},
    {0xB2, "Bandai"},
    {0xB4, "Enix"},
    {0xB6, "HAL"},
    {0xB7, "SNK"},
    {0xB9, "Pony Canyon"},
    {0xBA, "Culture Brain"},
    {0xBB, "Sunsoft"},
    {0xBD, "Sony Imagesoft"},
    {0xBF, "Sammy"},
    {0xC0, "Taito"},
    {0xC2, "Kemco"},
    {0xC3, "Squaresoft"},
    {0xC4, "Tokuma Shoten"},
    {0xC5, "Data East"},
    {0xC6, "Tonkin House"},
    {0xC8, "Koei"},
    {0xC9, "UFL"},
    {0xCA, "Ultra"},
    {0xCB, "Vap"},
    {0xCC, "Use Corporation"},
    {0xCD, "Meldac"},
    {0xCE, "Pony Canyon"},
    {0xCF, "Angel"},
    {0xD0, "Taito"},
    {0xD1, "Sofel"},
    {0xD2, "Quest"},
    {0xD3, "Sigma Enterprises"},
    {0xD4, "ASK Kodansha"},
    {0xD6, "Naxat Soft"},
    {0xD7, "Copya System"},
    {0xD9, "Banpresto"},
    {0xDA, "Tomy"},
    {0xDB, "LJN"},
    {0xDD, "NCS"},
    {0xDE, "Human"},
    {0xDF, "Altron"},
    {0xE0, "Jaleco"},
    {0xE1, "Towachiki"},
    {0xE2, "Uutaka"},
    {0xE3, "Varie"},
    {0xE5, "Epoch"},
    {0xE7, "Athena"},
    {0xE8, "Asmik ACE"},
    {0xE9, "Natsume"},
    {0xEA, "King Records"},
    {0xEB, "Atlus"},
    {0xEC, "Epic/Sony Records"},
    {0xEE, "IGS"},
    {0xF0, "A Wave"},
    {0xF3, "Extreme Entertainment"},
    {0xFF, "LJN"},
};
