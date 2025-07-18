#include "../../include/cpu.hpp"
#include "../../include/instructions.hpp"
#include "../../include/mmu.hpp"

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

void CPU::stack_push(uint8_t value) {
    regs.SP--;
    bus->write_data(regs.SP, value);
}

void CPU::stack_push16(uint16_t value) {
    regs.SP -= 2;
    bus->write_data16(regs.SP, value);
}

uint8_t CPU::stack_pop() {
    uint8_t value = bus->read_data(regs.SP);
    regs.SP++;
    return value;
}

uint16_t CPU::stack_pop16() {
    uint16_t value = bus->read_data16(regs.SP);
    regs.SP += 2;
    return value;
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

        regs.set_register(current_instruction.reg1.value(), regs.read_register(current_instruction.reg2.value()) + (char)fetch_data);
        return 0;
    }

    regs.set_register(current_instruction.reg1.value(), fetch_data);
}

int CPU::process_LDH() {
    if (current_instruction.reg1 == REG_TYPE::RT_A) {
        regs.set_register(current_instruction.reg1.value(), bus->read_data(0xFF00 | fetch_data));
    }
    else {
        bus->write_data(0xFF00 | fetch_data, regs.read_register(REG_TYPE::RT_A));
    }
    return 4;
}

int CPU::process_PUSH() {
    uint16_t high = (regs.read_register(current_instruction.reg1.value()) >> 8) & 0xFF;
    uint16_t low = regs.read_register(current_instruction.reg1.value()) & 0xFF;
    stack_push(high);
    stack_push(low);
    return 12;
}

int CPU::process_POP() {
    uint16_t low = stack_pop();
    uint16_t high = stack_pop();
    regs.set_register(current_instruction.reg1.value(), (high << 8) | low);

    if (current_instruction.reg1 == REG_TYPE::RT_AF) {
        regs.set_register(current_instruction.reg1.value(), ((high << 8) | low) & 0xFFF0);
    }
    return 12;
}