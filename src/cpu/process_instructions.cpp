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

int CPU::process_LD() {
    if (dest_is_mem) {
        if (current_instruction.reg2 >= REG_TYPE::RT_AF)
        {
            bus->write_data16(mem_dest, fetch_data);
        }
        else {
            bus->write_data(mem_dest, fetch_data);
        }
        return 4;
    }

    if (current_instruction.mode == ADDR_MODE::AM_HL_SPR) {
        regs.flags.set_h((regs.read_register(current_instruction.reg2.value()) & 0x0F) + (fetch_data & 0x0F) > 0x10);

        regs.flags.set_c((regs.read_register(current_instruction.reg2.value()) & 0xFF) + (fetch_data & 0xFF) >= 0x100);
    }
    // TODO
}
