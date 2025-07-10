#pragma once

#include "instructions.hpp"
#include "mmu.hpp"

#include <cstdint>
#include <memory>
#include <bitset>

struct FlagRegister {
private:
    static const size_t Z_pos = 7;
    static const size_t N_pos = 6;
    static const size_t H_pos = 5;
    static const size_t C_pos = 4;

    std::bitset<8> flags;
public:
    bool z() const { return flags.test(Z_pos); }
    bool n() const { return flags.test(N_pos); }
    bool h() const { return flags.test(H_pos); }
    bool c() const { return flags.test(C_pos); }

    void set_z(bool val) { flags.set(Z_pos, val); }
    void set_n(bool val) { flags.set(N_pos, val); }
    void set_h(bool val) { flags.set(H_pos, val); }
    void set_c(bool val) { flags.set(C_pos, val); }

    uint8_t get_byte() const {
        return static_cast<uint8_t>(flags.to_ulong());
    }
    void set_byte(uint8_t val) {
        flags = val & 0xF0;
    }
};

class RegisterFile {

    union RegisterPair {
        uint16_t word;
        struct {
            uint8_t low_reg;
            uint8_t high_reg;
        };
    };

    RegisterPair _af, _bc, _de, _hl;

public:
    FlagRegister flags;

    uint8_t& A = _af.high_reg, F = flags.get_byte();
    uint8_t& B = _bc.high_reg, C = _bc.low_reg;
    uint8_t& D = _de.high_reg, E = _de.low_reg;
    uint8_t& H = _hl.high_reg, L = _hl.low_reg;

    uint16_t& AF = _af.word;
    uint16_t& BC = _bc.word;
    uint16_t& DE = _de.word;
    uint16_t& HL = _hl.word;

    uint16_t SP, PC;

    RegisterFile() : SP(0xFFFE), PC(0x0100) {}

    uint16_t ReadRegister(REG_TYPE reg) {
        switch (reg) {
            case REG_TYPE::RT_A: return A;
            case REG_TYPE::RT_F: return flags.get_byte();
            case REG_TYPE::RT_B: return B;
            case REG_TYPE::RT_C: return C;
            case REG_TYPE::RT_D: return D;
            case REG_TYPE::RT_E: return E;
            case REG_TYPE::RT_H: return H;
            case REG_TYPE::RT_L: return L;
            case REG_TYPE::RT_AF: return AF;
            case REG_TYPE::RT_BC: return BC;
            case REG_TYPE::RT_DE: return DE;
            case REG_TYPE::RT_HL: return HL;
            case REG_TYPE::RT_SP: return SP;
            case REG_TYPE::RT_PC: return PC;
            default:
               std::cerr << "Error: Invalid register type" << std::endl;
               return 0;
        }
    }

    void set_register(REG_TYPE reg, uint16_t value) {
        switch (reg) {
            case REG_TYPE::RT_A: A = value & 0xFF; break;
            case REG_TYPE::RT_B: B = value & 0xFF; break;
            case REG_TYPE::RT_C: C = value & 0xFF; break;
            case REG_TYPE::RT_D: D = value & 0xFF; break;
            case REG_TYPE::RT_E: E = value & 0xFF; break;
            case REG_TYPE::RT_H: H = value & 0xFF; break;
            case REG_TYPE::RT_L: L = value & 0xFF; break;
            case REG_TYPE::RT_AF: AF = value & 0xFFFF; break;
            case REG_TYPE::RT_BC: BC = value & 0xFFFF; break;
            case REG_TYPE::RT_DE: DE = value & 0xFFFF; break;
            case REG_TYPE::RT_HL: HL = value & 0xFFFF; break;
            case REG_TYPE::RT_SP: SP = value & 0xFFFF; break;
            case REG_TYPE::RT_PC: PC = value & 0xFFFF; break;
            default:
                std::cerr << "Error: Invalid register type" << std::endl;
        }
    }
};

class CPU {
public:
    uint16_t fetch_data;
    uint16_t mem_dest;

    bool dest_is_mem;
    uint8_t current_opcode;
    Instruction current_instruction;
    bool halted;
    bool stepping;
    bool interrupt_master_enable;

    uint16_t reverse(uint16_t num);
    CPU();
    ~CPU();

    RegisterFile regs;
    std::shared_ptr<MMU> bus;

    bool cpu_step();
    void fetch_instruction();
    void decode_instruction();
    void execute_instruction(const Instruction& instruction);
};

