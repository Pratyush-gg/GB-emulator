#include "../../include/instructions.hpp"
#include "../../include/cpu.hpp"

#include <iostream>

//TODO

int CPU::decode_instruction() {
    this->mem_dest = 0;
    this->dest_is_mem = false;

    switch (current_instruction.mode) {
        case ADDR_MODE::AM_IMP:
            return 0;

        case ADDR_MODE::AM_R:
            fetch_data = regs.read_register(current_instruction.reg1.value());
            return 0;

        case ADDR_MODE::AM_R_D8:
            fetch_data = bus->read_data(regs.PC);
            regs.PC++;
            return 4;

        case ADDR_MODE::AM_D16:
            fetch_data = bus->read_data(regs.PC) | (bus->read_data(regs.PC + 1) << 8);
            regs.PC += 2;
            return 0;

        case ADDR_MODE::AM_MR_R:
            fetch_data = regs.read_register(current_instruction.reg2.value());
            mem_dest = regs.read_register(current_instruction.reg1.value());
            dest_is_mem = true;

            if (current_instruction.reg1 == REG_TYPE::RT_C) {
                mem_dest |= 0xFF00;
            }
            return 0;

        case ADDR_MODE::AM_R_MR:
            mem_dest = regs.read_register(current_instruction.reg2.value());

            if (current_instruction.reg1 == REG_TYPE::RT_C) {
                mem_dest |= 0xFF00;
            }
            fetch_data = bus->read_data(mem_dest);
            return 4;
// TODO

        default:
            std::cerr << "Error: Unknown addressing mode: " 
                << static_cast<int>(current_instruction.mode) 
                << " Opcode: " << std::hex << static_cast<int>(current_opcode) 
                << std::dec << std::endl;
            return 0;
    }
    return 0;
}
