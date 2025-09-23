#include "../../include/instructions.hpp"
#include "../../include/cpu.hpp"
#include "../../include/emu.hpp"

#include <iostream>

//TODO

int CPU::decode_instruction() {
    this->mem_dest = 0;
    this->dest_is_mem = false;

    switch (current_instruction.mode) {
        case ADDR_MODE::AM_IMP: {
            return 0;
        }

        case ADDR_MODE::AM_R: {
            fetch_data = regs.read_register(current_instruction.reg1.value());
            return 0;
        }

        case ADDR_MODE::AM_R_R: {
            fetch_data = regs.read_register(current_instruction.reg2.value());
            return 0;
        }

        case ADDR_MODE::AM_R_D8: {
            fetch_data = bus->read_data(regs.PC);
            regs.PC++;
            return 4;
        }

        case ADDR_MODE::AM_R_D16:

        case ADDR_MODE::AM_D16: {
            const uint16_t low = bus->read_data(regs.PC);
            const uint16_t high = bus->read_data(regs.PC + 1);
            fetch_data = low | (high << 8);
            regs.PC += 2;
            return 8;
        }

        case ADDR_MODE::AM_MR_R: {
            fetch_data = regs.read_register(current_instruction.reg2.value());
            mem_dest = regs.read_register(current_instruction.reg1.value());
            dest_is_mem = true;

            if (current_instruction.reg1 == REG_TYPE::RT_C) {
                mem_dest |= 0xFF00;
            }
            return 0;
        }

        case ADDR_MODE::AM_R_MR: {
            uint16_t addr = regs.read_register(current_instruction.reg2.value());

            if (current_instruction.reg2 == REG_TYPE::RT_C) {
                addr |= 0xFF00;
            }
            fetch_data = bus->read_data(addr);
            return 4;
        }

        case ADDR_MODE::AM_R_HLI: {
            fetch_data = bus->read_data(regs.read_register(current_instruction.reg2.value()));
            regs.set_register(REG_TYPE::RT_HL, regs.read_register(REG_TYPE::RT_HL) + 1);
            return 4;
        }

        case ADDR_MODE::AM_R_HLD: {
            fetch_data = bus->read_data(regs.read_register(current_instruction.reg2.value()));
            regs.set_register(REG_TYPE::RT_HL, regs.read_register(REG_TYPE::RT_HL) - 1);
            return 4;
        }

        case ADDR_MODE::AM_HLI_R: {
            fetch_data = regs.read_register(current_instruction.reg2.value());
            mem_dest = regs.read_register(current_instruction.reg1.value());
            dest_is_mem = true;
            regs.set_register(REG_TYPE::RT_HL, regs.read_register(REG_TYPE::RT_HL) + 1);
            return 0;
        }

        case ADDR_MODE::AM_HLD_R: {
            fetch_data = regs.read_register(current_instruction.reg2.value());
            mem_dest = regs.read_register(current_instruction.reg1.value());
            dest_is_mem = true;
            regs.set_register(REG_TYPE::RT_HL, regs.read_register(REG_TYPE::RT_HL) - 1);
            return 0;
        }

        case ADDR_MODE::AM_R_A8: {
            fetch_data = bus->read_data(regs.PC);
            regs.PC++;
            return 4;
        }

        case ADDR_MODE::AM_A8_R: {
            mem_dest = bus->read_data(regs.PC) | 0xFF00;
            regs.PC++;
            dest_is_mem = true;
            return 4;
        }

        case ADDR_MODE::AM_HL_SPR: {
            fetch_data = bus->read_data(regs.PC);
            regs.PC++;
            return 4;
        }

        case ADDR_MODE::AM_D8: {
            fetch_data = bus->read_data(regs.PC);
            regs.PC++;
            return 4;
        }

        case ADDR_MODE::AM_A16_R:

        case ADDR_MODE::AM_D16_R: {
            uint16_t low1 = bus->read_data(regs.PC);
            uint16_t high1 = bus->read_data(regs.PC + 1);
            mem_dest = low1 | (high1 << 8);
            dest_is_mem = true;
            fetch_data = regs.read_register(current_instruction.reg2.value());
            regs.PC += 2;
            return 8;
        }

        case ADDR_MODE::AM_MR_D8: {
            fetch_data = bus->read_data(regs.PC);
            mem_dest = regs.read_register(current_instruction.reg1.value());
            dest_is_mem = true;
            regs.PC++;
            return 4;
        }

        case ADDR_MODE::AM_MR: {
            mem_dest = regs.read_register(current_instruction.reg1.value());
            dest_is_mem = true;
            fetch_data = bus->read_data(regs.read_register(current_instruction.reg1.value()));
            return 4;
        }

        case ADDR_MODE::AM_R_A16: {
            uint16_t low2 = bus->read_data(regs.PC);
            uint16_t high2 = bus->read_data(regs.PC + 1);
            uint16_t addr2 = low2 | (high2 << 8);
            fetch_data = bus->read_data(addr2);
            regs.PC += 2;
            return 12;
        }

        default:
            std::cerr << "Error: Unknown addressing mode: "
                << static_cast<int>(current_instruction.mode)
                << " Opcode: " << std::hex << static_cast<int>(current_opcode)
                << std::dec << std::endl;
            return 0;
    }
    return 0;
}
