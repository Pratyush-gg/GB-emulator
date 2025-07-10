#include "../include/cpu.hpp"
#include "../include/instructions.hpp"
#include "../include/process_instructions.hpp"
#include "../include/mmu.hpp"
#include "../include/emu.hpp"

#include <iostream>
#include <cstdint>

Emulator emulator;

void CPU::fetch_instruction() {
    current_opcode = bus->read_data(regs.PC);
    regs.PC++;
    current_instruction = instructions[current_opcode];
    if (current_instruction.type == INST_TYPE::IN_NONE) {
        std::cerr << "Error: Unknown instruction at PC: " << std::hex << regs.PC - 1 << std::dec << std::endl;
        return;
    }
    emulator.cycles = 4;
}

//TODO

void CPU::execute_instruction(const Instruction& instruction) {
    switch (instruction.type) {
        case INST_TYPE::IN_NOP:
            process_NOP(*this);
            break;
        case INST_TYPE::IN_JP:
            process_JP(*this, emulator);
            break;
        case INST_TYPE::IN_XOR:
            process_XOR(*this);
            break;
        default:
            std::cerr << "Error: Unhandled instruction type: " << static_cast<int>(instruction.type) << std::endl;
            break;
    }
}

// void CPU::decode_instruction() {
//     Instruction &inst = this->current_instruction;
//     switch (inst.type) {
//         case INST_TYPE::IN_LD:
//             if (inst.mode == ADDR_MODE::AM_R_D16) {
//                 inst.param = bus->read_data(regs.PC) | (bus->read_data(regs.PC + 1) << 8);
//                 regs.PC += 2;
//             } else if (inst.mode == ADDR_MODE::AM_R_R) {
//                 // No additional data needed
//             } else if (inst.mode == ADDR_MODE::AM_MR_R) {
//                 inst.param = regs.get_register(inst.reg1.value());
//             }
//             break;
//         // Handle other instruction types...
//         default:
//             break;
//     }
// }

// TODO: figure out what this is
// void CPU::fetch_data() {
//     switch(cctx.current_instruction.mode) {
//         case address_mode::AM_IMP:
//             // No data to fetch
//             break;
//         case address_mode::AM_R_D16:
//             cctx.fetch_data = bus_read(cctx.regs.pc++) | (bus_read(cctx.regs.pc++) << 8);
//             break;
//         case address_mode::AM_R_R:
//             cctx.fetch_data = cctx.regs.get_register(cctx.current_instruction.reg2);
//             break;
//         case address_mode::AM_MR_R:
//             cctx.mem_dest = cctx.regs.get_register(cctx.current_instruction.reg1);
//             cctx.dest_is_mem = true;
//             break;
//         case address_mode::AM_R:
//             cctx.fetch_data = cctx.regs.get_register(cctx.current_instruction.reg1);
//             break;
//         case address_mode::AM_R_D8:
//             cctx.fetch_data = bus_read(cctx.regs.pc++);
//             break;
//         case address_mode::AM_R_MR:
//             cctx.mem_dest = cctx.regs.get_register(cctx.current_instruction.reg1);
//             cctx.dest_is_mem = true;
//             break;
//         case address_mode::AM_R_HLI:
//             cctx.mem_dest = cctx.regs.hl();
//             cctx.dest_is_mem = true;
//             cctx.regs.hl_inc();
//             break;
//         case address_mode::AM_R_HLD:
//             cctx.mem_dest = cctx.regs.hl();
//             cctx.dest_is_mem = true;
//             cctx.regs.hl_dec();
//             break;
//         case address_mode::AM_HLI_R:
//             bus_write(cctx.regs.hl(), cctx.regs.get_register(cctx.current_instruction.reg1));
//             break;
//         case address_mode::AM_HLD_R:
//             bus_write(cctx.regs.hl(), cctx.regs.get_register(cctx.current_instruction.reg1));
//             break;
//         case address_mode::AM_R_A8:
//             cctx.fetch_data = bus_read(bus_read(cctx.regs.pc++));
//             break;
//         case address_mode::AM_A8_R:
//             bus_write(bus_read(cctx.regs.pc++), cctx.regs.get_register(cctx.current_instruction.reg1));
//             break;
//         case address_mode::AM_HL_SPR:
//             // Not implemented
//             break;
//         case address_mode::AM_D16:
//             // Not implemented
//             break;
//         case address_mode::AM_D8:
//             cctx.fetch_data = bus_read(cctx.regs.pc++);
//             break;
//         case address_mode::AM_D16_R:
//             cctx.fetch_data = bus_read(cctx.regs.pc++) | (bus_read(cctx.regs.pc++) << 8);
//             cctx.regs.set_register(cctx.current_instruction.reg1, cctx.fetch_data);
//             break;
//         case address_mode::AM_MR_D8:
//             cctx.mem_dest = bus_read(cctx.regs.pc++);
//             cctx.dest_is_mem = true;
//             cctx.fetch_data = bus_read(cctx.mem_dest);
//             break;
//         case address_mode::AM_MR:
//             cctx.mem_dest = cctx.regs.get_register(cctx.current_instruction.reg1);
//             cctx.dest_is_mem = true;
//             cctx.fetch_data = bus_read(cctx.mem_dest);
//             break;
//         case address_mode::AM_A16_R:
//             cctx.mem_dest = bus_read(cctx.regs.pc++) | (bus_read(cctx.regs.pc++) << 8);
//             cctx.dest_is_mem = true;
//             cctx.fetch_data = bus_read(cctx.mem_dest);
//             break;
//         case address_mode::AM_R_A16:
//             cctx.mem_dest = bus_read(cctx.regs.pc++) | (bus_read(cctx.regs.pc++) << 8);
//             cctx.dest_is_mem = true;
//             bus_write(cctx.mem_dest, cctx.regs.get_register(cctx.current_instruction.reg1));
//             break;
//         // Done by AI check !!
//         default:
//             cout << "Error: Unknown addressing mode " << static_cast<int>(cctx.current_instruction.mode) << endl;
//             break;
// }
//
// bool cpu_step() {
//     if (!cctx.halted) {
//         fetch_instruction();
//         fetch_data();
//         execute_instruction();
//     }
//     return true;
// }
