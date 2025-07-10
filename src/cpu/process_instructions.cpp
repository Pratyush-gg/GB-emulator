#include "../../include/cpu.hpp"
#include "../../include/emu.hpp"
#include "../../include/instructions.hpp"
#include "../../include/process_instructions.hpp"

#include <iostream>

// TODO

bool check_condition(CPU& cpu, const Instruction& instruction) {
    if (!instruction.condition.has_value()) {
        return true;
    }
    switch (instruction.condition.value()) {
        case COND_TYPE::CT_NONE:
            return true;
        case COND_TYPE::CT_Z:
            return cpu.regs.flags.z();
        case COND_TYPE::CT_NZ:
            return !cpu.regs.flags.z();
        case COND_TYPE::CT_C:
            return cpu.regs.flags.c();
        case COND_TYPE::CT_NC:
            return !cpu.regs.flags.c();
        default:
            std::cerr << "Error: Unknown condition type" << std::endl;
            return false;
    }
}

void process_NOP(CPU& cpu) {}

void process_DI(CPU& cpu) {
    cpu.interrupt_master_enable = false;
}

void process_JP(CPU& cpu, Emulator& emulator) {
    if (check_condition(cpu, cpu.current_instruction)) {
        cpu.regs.PC = cpu.fetch_data;
        emulator.cycles += 4;
    }
}

void process_XOR(CPU& cpu) {
    uint8_t value = cpu.fetch_data & 0xFF;
    cpu.regs.A ^= value;
    cpu.regs.flags.set_z(cpu.regs.A == 0);
}