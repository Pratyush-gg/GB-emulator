#include "../../include/instructions.hpp"
#include "../../include/cpu.hpp"
#include "../../include/emu.hpp"

#include <iostream>
Emulator emulator;

//TODO

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
        case ADDR_MODE::AM_MR_R:
            fetch_data = regs.ReadRegister(current_instruction.reg2.value());
            mem_dest = regs.ReadRegister(current_instruction.reg1.value());
            dest_is_mem = true;

            if (current_instruction.reg1 == REG_TYPE::RT_C) {
                mem_dest |= 0xFF00;
            }
            return;
        case ADDR_MODE::AM_R_MR:
            mem_dest = regs.ReadRegister(current_instruction.reg2.value());

            if (current_instruction.reg1 == REG_TYPE::RT_C) {
                mem_dest |= 0xFF00;
            }
            fetch_data = bus->read_data(mem_dest);
            emulator.cycles += 4;
            return;
// TODO

        default:
            std::cerr << "Error: Unknown addressing mode: " << static_cast<int>(current_instruction.mode) << " Opcode: " << std::hex << static_cast<int>(current_opcode) << std::dec << std::endl;
            return;
}