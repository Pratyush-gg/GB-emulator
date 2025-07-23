#include "../../include/cpu.hpp"
#include "../../include/instructions.hpp"

#include <iostream>
#include <iomanip>

int CPU::fetch_instruction() {
    current_opcode = bus->read_data(regs.PC++);
    current_instruction = instructions[current_opcode];
    if (current_instruction.type == INST_TYPE::IN_NONE) {
        std::cerr << "Error: Unknown instruction" << std::endl;
        return 0;
    }
    return 4;
}

//TODO

int CPU::execute_instruction(const Instruction& instruction) {
    switch (instruction.type) {
        case INST_TYPE::IN_NOP: return process_NOP();
        case INST_TYPE::IN_DI:  return process_DI();
        case INST_TYPE::IN_JP:  return process_JP();
        case INST_TYPE::IN_XOR: return process_XOR();
        case INST_TYPE::IN_LD:  return process_LD();
        case INST_TYPE::IN_LDH: return process_LDH();
        case INST_TYPE::IN_PUSH: return process_PUSH();
        case INST_TYPE::IN_POP:  return process_POP();
        case INST_TYPE::IN_JR:   return process_JR();
        case INST_TYPE::IN_CALL: return process_CALL();
        case INST_TYPE::IN_RST:  return process_RST();
        case INST_TYPE::IN_RET:  return process_RET();
        case INST_TYPE::IN_RETI: return process_RETI();
        case INST_TYPE::IN_INC:  return process_INC();
        case INST_TYPE::IN_DEC:  return process_DEC();
        case INST_TYPE::IN_SUB:  return process_SUB();
        case INST_TYPE::IN_ADD:  return process_ADD();
        case INST_TYPE::IN_ADC:  return process_ADC();
        case INST_TYPE::IN_SBC:  return process_SBC();

        default:
            std::cerr << "Error: Unhandled instruction type: " << static_cast<int>(instruction.type) << std::endl;
            return 1;
    }
    return 0;
}

int CPU::cpu_step() {
    if (!halted) {
        uint16_t prev_PC = regs.PC;

        int num_cycles = 0;

        num_cycles += fetch_instruction();
        num_cycles += decode_instruction();

        std::cout << "PC: " << std::hex << prev_PC << std::dec << " Opcode: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(current_opcode) << std::dec;
        std::cout << " A: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._a);
        std::cout << " F: " << (regs.flags.c() ? 'C' : '_') << (regs.flags.h() ? 'H' : '_') << (regs.flags.n() ? 'N' : '_') << (regs.flags.z() ? 'Z' : '_');
        std::cout << " BC: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._b) << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._c) << std::dec;
        std::cout << " DE: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._d) << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._e) << std::dec;
        std::cout << " HL: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._h) << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._l) << std::dec << std::endl;
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bus->read_data(regs.PC)) << " " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bus->read_data(regs.PC + 1)) << std::endl;

        int res = execute_instruction(current_instruction);

        if (res == 1) return 0;
        else num_cycles += res;

        return num_cycles;
    }
    // Look into this halted paused running thing
    return 0;
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
