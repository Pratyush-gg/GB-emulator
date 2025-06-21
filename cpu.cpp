#include "gb_utils.hpp"
#include "cpu.hpp"
#include "instructions.hpp"
#include "emu.hpp"

cpu_context cctx;

void cpu_init() {
    cctx.regs.pc = 0x100;
}

void fetch_instruction() {
    cctx.current_opcode = bus_read(cctx.regs.pc++);
    else if (instructions[cctx.current_opcode].type == instruction_type::IN_NONE) {
        cout << "Error: Invalid opcode " << hex << (int)cctx.current_opcode << " at PC: " << hex << cctx.regs.pc << endl;
        return;
    }
    cctx.current_instruction = instructions[cctx.current_opcode];
    if (cctx.current_instruction == NULL) {
        cout << "Error: Unknown instruction! " << hex << (int)cctx.current_opcode << " at PC: " << hex << cctx.regs.pc << endl;
        return;
    }
}

void fetch_data() {
    cctx.mem_dest = 0;
    cctx.dest_is_mem = false;
    switch(cctx.current_instruction.mode) {
        case address_mode::AM_IMP:
            // No data to fetch
            break;
        case address_mode::AM_R_D16:
            cctx.fetch_data = bus_read(cctx.regs.pc++) | (bus_read(cctx.regs.pc++) << 8);
            break;
        case address_mode::AM_R_R:
            cctx.fetch_data = cctx.regs.get_register(cctx.current_instruction.reg2);
            break;
        case address_mode::AM_MR_R:
            cctx.mem_dest = cctx.regs.get_register(cctx.current_instruction.reg1);
            cctx.dest_is_mem = true;
            break;
        case address_mode::AM_R:
            cctx.fetch_data = cctx.regs.get_register(cctx.current_instruction.reg1);
            break;
        case address_mode::AM_R_D8:
            cctx.fetch_data = bus_read(cctx.regs.pc++);
            break;
        case address_mode::AM_R_MR:
            cctx.mem_dest = cctx.regs.get_register(cctx.current_instruction.reg1);
            cctx.dest_is_mem = true;
            break;
        case address_mode::AM_R_HLI:
            cctx.mem_dest = cctx.regs.hl();
            cctx.dest_is_mem = true;
            cctx.regs.hl_inc();
            break;
        case address_mode::AM_R_HLD:
            cctx.mem_dest = cctx.regs.hl();
            cctx.dest_is_mem = true;
            cctx.regs.hl_dec();
            break;
        case address_mode::AM_HLI_R:
            bus_write(cctx.regs.hl(), cctx.regs.get_register(cctx.current_instruction.reg1));
            break;
        case address_mode::AM_HLD_R:
            bus_write(cctx.regs.hl(), cctx.regs.get_register(cctx.current_instruction.reg1));
            break;
        case address_mode::AM_R_A8:
            cctx.fetch_data = bus_read(bus_read(cctx.regs.pc++));
            break;
        case address_mode::AM_A8_R:
            bus_write(bus_read(cctx.regs.pc++), cctx.regs.get_register(cctx.current_instruction.reg1));
            break;
        case address_mode::AM_HL_SPR:
            // Not implemented
            break;
        case address_mode::AM_D16:
            // Not implemented
            break;
        case address_mode::AM_D8:
            cctx.fetch_data = bus_read(cctx.regs.pc++);
            break;
        case address_mode::AM_D16_R:
            cctx.fetch_data = bus_read(cctx.regs.pc++) | (bus_read(cctx.regs.pc++) << 8);
            cctx.regs.set_register(cctx.current_instruction.reg1, cctx.fetch_data);
            break;
        case address_mode::AM_MR_D8:
            cctx.mem_dest = bus_read(cctx.regs.pc++);
            cctx.dest_is_mem = true;
            cctx.fetch_data = bus_read(cctx.mem_dest);
            break;
        case address_mode::AM_MR:
            cctx.mem_dest = cctx.regs.get_register(cctx.current_instruction.reg1);
            cctx.dest_is_mem = true;
            cctx.fetch_data = bus_read(cctx.mem_dest);
            break;
        case address_mode::AM_A16_R:
            cctx.mem_dest = bus_read(cctx.regs.pc++) | (bus_read(cctx.regs.pc++) << 8);
            cctx.dest_is_mem = true;
            cctx.fetch_data = bus_read(cctx.mem_dest);
            break;
        case address_mode::AM_R_A16:
            cctx.mem_dest = bus_read(cctx.regs.pc++) | (bus_read(cctx.regs.pc++) << 8);
            cctx.dest_is_mem = true;
            bus_write(cctx.mem_dest, cctx.regs.get_register(cctx.current_instruction.reg1));
            break;
        // Done by AI check !!
        default:
            cout << "Error: Unknown addressing mode " << static_cast<int>(cctx.current_instruction.mode) << endl;
            break;
}

bool cpu_step() {
    if (!cctx.halted) {
        fetch_instruction();
        fetch_data();
        execute_instruction();
    }

    return true;
}