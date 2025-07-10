#include "../../include/cpu.hpp"
#include "../../include/instructions.hpp"

#include <iostream>

// TODO

bool CPU::check_condition(const Instruction& instruction) {
    if (!instruction.condition.has_value()) {
        return true;
    }

    switch (instruction.condition.value()) {
        case COND_TYPE::CT_NONE:
            return true;
        case COND_TYPE::CT_Z:
            return regs.flags.z();
        case COND_TYPE::CT_NZ:
            return !regs.flags.z();
        case COND_TYPE::CT_C:
            return regs.flags.c();
        case COND_TYPE::CT_NC:
            return !regs.flags.c();
        default:
            std::cerr << "Error: Unknown condition type" << std::endl;
            return false;
    }
}

int CPU::process_NOP() {
    return 0;
}

int CPU::process_DI() {
    this->interrupt_master_enable = false;
    return 0;
}

int CPU::process_JP() {
    if (check_condition(current_instruction)) {
        regs.PC = fetch_data;
        return 4;
    }
    return 0;
}

int CPU::process_XOR() {
    uint8_t value = fetch_data & 0xFF;
    regs._a ^= value;
    regs.flags.set_z(regs._a == 0);
    return 0;
}
