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

    FlagRegister& operator=(uint8_t value) {
        this->set_byte(value);
        return *this;
    }
};

class RegisterFile {
public:
    uint8_t _a, _b, _c, _d, _e, _h, _l;

    FlagRegister flags;
    uint16_t SP, PC;

    RegisterFile() : SP(0xFFFE), PC(0x0100), 
                     _a(0), _b(0), _c(0), _d(0), _e(0), _h(0), _l(0) {}

    uint16_t read_register(REG_TYPE reg);
    void set_register(REG_TYPE reg, uint16_t value);
};

class CPU {
public:
    CPU(const std::shared_ptr<MMU> _mmu): bus(_mmu) {}

    uint16_t fetch_data;
    uint16_t mem_dest;

    bool dest_is_mem;
    uint8_t current_opcode;
    Instruction current_instruction;
    bool halted;
    bool stepping;
    bool interrupt_master_enable;


    RegisterFile regs;

    int cpu_step(); 
    int fetch_instruction();
    int decode_instruction();
    int execute_instruction(const Instruction& instruction);

private:
    std::shared_ptr<MMU> bus;

    uint16_t reverse(uint16_t num);

    bool check_condition(const Instruction& instruction);
    // ts returns the number of cycles taken now
    int process_NOP();
    int process_DI();
    int process_JP();
    int process_XOR();
};
