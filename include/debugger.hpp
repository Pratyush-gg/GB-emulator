//
// Created by shawn on 25-09-2025.
//

#pragma once
#include "SFML/Window/Keyboard.hpp"

static constexpr int scale = 2.0;

#include <iostream>
#include <memory>
#include <ostream>
#include <stack>
#include <unordered_set>
#include <vector>
#include <array>
#include <thread>
#include <mutex>
#include <atomic>
#include <SFML/Graphics/Texture.hpp>

#include "emu.hpp"

struct debuggerInst {
    std::string mnemonic;
    uint8_t length;
    uint8_t immediate;
};

extern debuggerInst instr_table[256];

class Debugger {
    std::string romFilename;
    std::shared_ptr<Emulator> emu;
    DebugContext debugContext;
    unsigned disassembler_num_lines = 100;

    uint16_t hexview_curr_mem = 0x100;
    unsigned hexview_num_lines = 30;
    unsigned hexview_num_cols = 8;

    std::stack<uint16_t> return_points;
    std::unordered_set<uint16_t> breakpoints;

    uint16_t getCurrentInstruction() const {
        return debugContext.regs.get().PC;
    }

    uint16_t getNextInstruction() const {
        return getNextInstruction(debugContext.regs.get().PC);
    }

    uint16_t getNextInstruction(const uint16_t instruction) const {
        const int sz = instr_table[debugContext.mmu.get().read_data(instruction)].length;
        return instruction + sz;
    }

    bool running = false;
    bool checkStack = false;

    uint64_t instPerFrame = (1ull << 20);

    void stepIn();
    void stepOut();
    void stepOver();
    void runContinue();
    void toggleBreakpoint(uint16_t address);
    void inLoop();
    void reload_rom();
    void handle_command(char *commandBuffer);

    char prevCommandBuffer[256] = "s\0";

    static constexpr unsigned int TILE_DATA_WIDTH_PX = 16 * 8;
    static constexpr unsigned int TILE_DATA_HEIGHT_PX = 24 * 8;

    sf::Texture tile_texture;
    std::vector<sf::Uint8> tile_pixel_buffer;

private:
    void emulator_thread_loop(); // The main function for our new thread

    std::thread emu_thread;
    std::mutex emu_mutex; // Protects access to the emulator state and debugContext

    std::atomic<bool> emu_running = false; // Controls if the emulator is running or paused
    std::atomic<bool> shutdown_thread = false;    // Signals the thread to exit cleanly

public:
    explicit Debugger(const std::string& filename);
    ~Debugger();

    uint32_t getCurrentFrame() const;
    void render();
    void render_hex_view();
    void render_registers_panel();
    void render_command_prompt();
    void render_disassembly_panel();
    void render_tile_data_panel();
    void get_video_buffer(std::array<uint32_t, 160 * 144>& out_buffer);
    void handle_input(sf::Keyboard::Key key, bool is_pressed);
};

inline debuggerInst instr_table[256] = {
    // 0x0_
    {"NOP", 1, 0},          // 0x00
    {"LD BC, d16", 3, 2},   // 0x01
    {"LD (BC), A", 1, 0},   // 0x02
    {"INC BC", 1, 0},       // 0x03
    {"INC B", 1, 0},        // 0x04
    {"DEC B", 1, 0},        // 0x05
    {"LD B, d8", 2, 1},     // 0x06
    {"RLCA", 1, 0},         // 0x07
    {"LD (a16), SP", 3, 2}, // 0x08
    {"ADD HL, BC", 1, 0},   // 0x09
    {"LD A, (BC)", 1, 0},   // 0x0a
    {"DEC BC", 1, 0},       // 0x0b
    {"INC C", 1, 0},        // 0x0c
    {"DEC C", 1, 0},        // 0x0d
    {"LD C, d8", 2, 1},     // 0x0e
    {"RRCA", 1, 0},         // 0x0f

    // 0x1_
    {"STOP", 2, 1},         // 0x10
    {"LD DE, d16", 3, 2},   // 0x11
    {"LD (DE), A", 1, 0},   // 0x12
    {"INC DE", 1, 0},       // 0x13
    {"INC D", 1, 0},        // 0x14
    {"DEC D", 1, 0},        // 0x15
    {"LD D, d8", 2, 1},     // 0x16
    {"RLA", 1, 0},          // 0x17
    {"JR r8", 2, 1},        // 0x18
    {"ADD HL, DE", 1, 0},   // 0x19
    {"LD A, (DE)", 1, 0},   // 0x1a
    {"DEC DE", 1, 0},       // 0x1b
    {"INC E", 1, 0},        // 0x1c
    {"DEC E", 1, 0},        // 0x1d
    {"LD E, d8", 2, 1},     // 0x1e
    {"RRA", 1, 0},          // 0x1f

    // 0x2_
    {"JR NZ, r8", 2, 1},    // 0x20
    {"LD HL, d16", 3, 2},   // 0x21
    {"LD (HL+), A", 1, 0},  // 0x22
    {"INC HL", 1, 0},       // 0x23
    {"INC H", 1, 0},        // 0x24
    {"DEC H", 1, 0},        // 0x25
    {"LD H, d8", 2, 1},     // 0x26
    {"DAA", 1, 0},          // 0x27
    {"JR Z, r8", 2, 1},     // 0x28
    {"ADD HL, HL", 1, 0},   // 0x29
    {"LD A, (HL+)", 1, 0},  // 0x2a
    {"DEC HL", 1, 0},       // 0x2b
    {"INC L", 1, 0},        // 0x2c
    {"DEC L", 1, 0},        // 0x2d
    {"LD L, d8", 2, 1},     // 0x2e
    {"CPL", 1, 0},          // 0x2f

    // 0x3_
    {"JR NC, r8", 2, 1},    // 0x30
    {"LD SP, d16", 3, 2},   // 0x31
    {"LD (HL-), A", 1, 0},  // 0x32
    {"INC SP", 1, 0},       // 0x33
    {"INC (HL)", 1, 0},     // 0x34
    {"DEC (HL)", 1, 0},     // 0x35
    {"LD (HL), d8", 2, 1},  // 0x36
    {"SCF", 1, 0},          // 0x37
    {"JR C, r8", 2, 1},     // 0x38
    {"ADD HL, SP", 1, 0},   // 0x39
    {"LD A, (HL-)", 1, 0},  // 0x3a
    {"DEC SP", 1, 0},       // 0x3b
    {"INC A", 1, 0},        // 0x3c
    {"DEC A", 1, 0},        // 0x3d
    {"LD A, d8", 2, 1},     // 0x3e
    {"CCF", 1, 0},          // 0x3f

    // 0x4_
    {"LD B, B", 1, 0},      // 0x40
    {"LD B, C", 1, 0},      // 0x41
    {"LD B, D", 1, 0},      // 0x42
    {"LD B, E", 1, 0},      // 0x43
    {"LD B, H", 1, 0},      // 0x44
    {"LD B, L", 1, 0},      // 0x45
    {"LD B, (HL)", 1, 0},   // 0x46
    {"LD B, A", 1, 0},      // 0x47
    {"LD C, B", 1, 0},      // 0x48
    {"LD C, C", 1, 0},      // 0x49
    {"LD C, D", 1, 0},      // 0x4a
    {"LD C, E", 1, 0},      // 0x4b
    {"LD C, H", 1, 0},      // 0x4c
    {"LD C, L", 1, 0},      // 0x4d
    {"LD C, (HL)", 1, 0},   // 0x4e
    {"LD C, A", 1, 0},      // 0x4f

    // 0x5_
    {"LD D, B", 1, 0},      // 0x50
    {"LD D, C", 1, 0},      // 0x51
    {"LD D, D", 1, 0},      // 0x52
    {"LD D, E", 1, 0},      // 0x53
    {"LD D, H", 1, 0},      // 0x54
    {"LD D, L", 1, 0},      // 0x55
    {"LD D, (HL)", 1, 0},   // 0x56
    {"LD D, A", 1, 0},      // 0x57
    {"LD E, B", 1, 0},      // 0x58
    {"LD E, C", 1, 0},      // 0x59
    {"LD E, D", 1, 0},      // 0x5a
    {"LD E, E", 1, 0},      // 0x5b
    {"LD E, H", 1, 0},      // 0x5c
    {"LD E, L", 1, 0},      // 0x5d
    {"LD E, (HL)", 1, 0},   // 0x5e
    {"LD E, A", 1, 0},      // 0x5f

    // 0x6_
    {"LD H, B", 1, 0},      // 0x60
    {"LD H, C", 1, 0},      // 0x61
    {"LD H, D", 1, 0},      // 0x62
    {"LD H, E", 1, 0},      // 0x63
    {"LD H, H", 1, 0},      // 0x64
    {"LD H, L", 1, 0},      // 0x65
    {"LD H, (HL)", 1, 0},   // 0x66
    {"LD H, A", 1, 0},      // 0x67
    {"LD L, B", 1, 0},      // 0x68
    {"LD L, C", 1, 0},      // 0x69
    {"LD L, D", 1, 0},      // 0x6a
    {"LD L, E", 1, 0},      // 0x6b
    {"LD L, H", 1, 0},      // 0x6c
    {"LD L, L", 1, 0},      // 0x6d
    {"LD L, (HL)", 1, 0},   // 0x6e
    {"LD L, A", 1, 0},      // 0x6f

    // 0x7_
    {"LD (HL), B", 1, 0},   // 0x70
    {"LD (HL), C", 1, 0},   // 0x71
    {"LD (HL), D", 1, 0},   // 0x72
    {"LD (HL), E", 1, 0},   // 0x73
    {"LD (HL), H", 1, 0},   // 0x74
    {"LD (HL), L", 1, 0},   // 0x75
    {"HALT", 1, 0},         // 0x76
    {"LD (HL), A", 1, 0},   // 0x77
    {"LD A, B", 1, 0},      // 0x78
    {"LD A, C", 1, 0},      // 0x79
    {"LD A, D", 1, 0},      // 0x7a
    {"LD A, E", 1, 0},      // 0x7b
    {"LD A, H", 1, 0},      // 0x7c
    {"LD A, L", 1, 0},      // 0x7d
    {"LD A, (HL)", 1, 0},   // 0x7e
    {"LD A, A", 1, 0},      // 0x7f

    // 0x8_
    {"ADD A, B", 1, 0},     // 0x80
    {"ADD A, C", 1, 0},     // 0x81
    {"ADD A, D", 1, 0},     // 0x82
    {"ADD A, E", 1, 0},     // 0x83
    {"ADD A, H", 1, 0},     // 0x84
    {"ADD A, L", 1, 0},     // 0x85
    {"ADD A, (HL)", 1, 0},  // 0x86
    {"ADD A, A", 1, 0},     // 0x87
    {"ADC A, B", 1, 0},     // 0x88
    {"ADC A, C", 1, 0},     // 0x89
    {"ADC A, D", 1, 0},     // 0x8a
    {"ADC A, E", 1, 0},     // 0x8b
    {"ADC A, H", 1, 0},     // 0x8c
    {"ADC A, L", 1, 0},     // 0x8d
    {"ADC A, (HL)", 1, 0},  // 0x8e
    {"ADC A, A", 1, 0},     // 0x8f

    // 0x9_
    {"SUB B", 1, 0},        // 0x90
    {"SUB C", 1, 0},        // 0x91
    {"SUB D", 1, 0},        // 0x92
    {"SUB E", 1, 0},        // 0x93
    {"SUB H", 1, 0},        // 0x94
    {"SUB L", 1, 0},        // 0x95
    {"SUB (HL)", 1, 0},     // 0x96
    {"SUB A", 1, 0},        // 0x97
    {"SBC A, B", 1, 0},     // 0x98
    {"SBC A, C", 1, 0},     // 0x99
    {"SBC A, D", 1, 0},     // 0x9a
    {"SBC A, E", 1, 0},     // 0x9b
    {"SBC A, H", 1, 0},     // 0x9c
    {"SBC A, L", 1, 0},     // 0x9d
    {"SBC A, (HL)", 1, 0},  // 0x9e
    {"SBC A, A", 1, 0},     // 0x9f

    // 0xA_
    {"AND B", 1, 0},        // 0xa0
    {"AND C", 1, 0},        // 0xa1
    {"AND D", 1, 0},        // 0xa2
    {"AND E", 1, 0},        // 0xa3
    {"AND H", 1, 0},        // 0xa4
    {"AND L", 1, 0},        // 0xa5
    {"AND (HL)", 1, 0},     // 0xa6
    {"AND A", 1, 0},        // 0xa7
    {"XOR B", 1, 0},        // 0xa8
    {"XOR C", 1, 0},        // 0xa9
    {"XOR D", 1, 0},        // 0xaa
    {"XOR E", 1, 0},        // 0xab
    {"XOR H", 1, 0},        // 0xac
    {"XOR L", 1, 0},        // 0xad
    {"XOR (HL)", 1, 0},     // 0xae
    {"XOR A", 1, 0},        // 0xaf

    // 0xB_
    {"OR B", 1, 0},         // 0xb0
    {"OR C", 1, 0},         // 0xb1
    {"OR D", 1, 0},         // 0xb2
    {"OR E", 1, 0},         // 0xb3
    {"OR H", 1, 0},         // 0xb4
    {"OR L", 1, 0},         // 0xb5
    {"OR (HL)", 1, 0},      // 0xb6
    {"OR A", 1, 0},         // 0xb7
    {"CP B", 1, 0},         // 0xb8
    {"CP C", 1, 0},         // 0xb9
    {"CP D", 1, 0},         // 0xba
    {"CP E", 1, 0},         // 0xbb
    {"CP H", 1, 0},         // 0xbc
    {"CP L", 1, 0},         // 0xbd
    {"CP (HL)", 1, 0},      // 0xbe
    {"CP A", 1, 0},         // 0xbf

    // 0xC_
    {"RET NZ", 1, 0},       // 0xc0
    {"POP BC", 1, 0},       // 0xc1
    {"JP NZ, a16", 3, 2},   // 0xc2
    {"JP a16", 3, 2},       // 0xc3
    {"CALL NZ, a16", 3, 2}, // 0xc4
    {"PUSH BC", 1, 0},      // 0xc5
    {"ADD A, d8", 2, 1},    // 0xc6
    {"RST 00H", 1, 0},      // 0xc7
    {"RET Z", 1, 0},        // 0xc8
    {"RET", 1, 0},          // 0xc9
    {"JP Z, a16", 3, 2},    // 0xca
    {"PREFIX CB", 1, 0},    // 0xcb
    {"CALL Z, a16", 3, 2},  // 0xcc
    {"CALL a16", 3, 2},     // 0xcd
    {"ADC A, d8", 2, 1},    // 0xce
    {"RST 08H", 1, 0},      // 0xcf

    // 0xD_
    {"RET NC", 1, 0},       // 0xd0
    {"POP DE", 1, 0},       // 0xd1
    {"JP NC, a16", 3, 2},   // 0xd2
    {"-", 1, 0},            // 0xd3 (illegal)
    {"CALL NC, a16", 3, 2}, // 0xd4
    {"PUSH DE", 1, 0},      // 0xd5
    {"SUB d8", 2, 1},       // 0xd6
    {"RST 10H", 1, 0},      // 0xd7
    {"RET C", 1, 0},        // 0xd8
    {"RETI", 1, 0},         // 0xd9
    {"JP C, a16", 3, 2},    // 0xda
    {"-", 1, 0},            // 0xdb (illegal)
    {"CALL C, a16", 3, 2},  // 0xdc
    {"-", 1, 0},            // 0xdd (illegal)
    {"SBC A, d8", 2, 1},    // 0xde
    {"RST 18H", 1, 0},      // 0xdf

    // 0xE_
    {"LDH (a8), A", 2, 1},  // 0xe0
    {"POP HL", 1, 0},       // 0xe1
    {"LD (C), A", 1, 0},    // 0xe2
    {"-", 1, 0},            // 0xe3 (illegal)
    {"-", 1, 0},            // 0xe4 (illegal)
    {"PUSH HL", 1, 0},      // 0xe5
    {"AND d8", 2, 1},       // 0xe6
    {"RST 20H", 1, 0},      // 0xe7
    {"ADD SP, r8", 2, 1},   // 0xe8
    {"JP (HL)", 1, 0},      // 0xe9
    {"LD (a16), A", 3, 2},  // 0xea
    {"-", 1, 0},            // 0xeb (illegal)
    {"-", 1, 0},            // 0xec (illegal)
    {"-", 1, 0},            // 0xed (illegal)
    {"XOR d8", 2, 1},       // 0xee
    {"RST 28H", 1, 0},      // 0xef

    // 0xF_
    {"LDH A, (a8)", 2, 1},  // 0xf0
    {"POP AF", 1, 0},       // 0xf1
    {"LD A, (C)", 1, 0},    // 0xf2
    {"DI", 1, 0},           // 0xf3
    {"-", 1, 0},            // 0xf4 (illegal)
    {"PUSH AF", 1, 0},      // 0xf5
    {"OR d8", 2, 1},        // 0xf6
    {"RST 30H", 1, 0},      // 0xf7
    {"LD HL, SP+r8", 2, 1}, // 0xf8
    {"LD SP, HL", 1, 0},    // 0xf9
    {"LD A, (a16)", 3, 2},  // 0xfa
    {"EI", 1, 0},           // 0xfb
    {"-", 1, 0},            // 0xfc (illegal)
    {"-", 1, 0},            // 0xfd (illegal)
    {"CP d8", 2, 1},        // 0xfe
    {"RST 38H", 1, 0},      // 0xff
};