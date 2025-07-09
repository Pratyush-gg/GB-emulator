#include "../include/instructions.hpp"
#include "../include/cpu.hpp"
#include "../include/emu.hpp"

#include <iostream>
Emulator emulator;

void CPU::decode_instruction() {
    mem_dest = 0;
    dest_is_mem = false;

    switch (current_instruction.mode) {
        case ADDR_MODE::AM_IMP:
            return;
        case ADDR_MODE::AM_R:
            fetch_data = regs.ReadRegister(current_instruction.reg1.value());
            return;
        case ADDR_MODE::AM_R_D8:
            fetch_data = bus->read_data(regs.PC);
            emulator.cycles += 4;
            regs.PC++;
            return;
        case ADDR_MODE::AM_D16:
            fetch_data = bus->read_data(regs.PC) | (bus->read_data(regs.PC + 1) << 8);
            emulator.cycles += 8;
            regs.PC += 2;
            return;

        default:
            std::cerr << "Error: Unknown addressing mode: " << static_cast<int>(current_instruction.mode) << std::endl;
            return;
}