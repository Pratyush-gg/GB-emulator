#pragma once
#include "gb_utils.hpp"

typedef struct {
    u8 a, f, b, c, d, e, h, l;
    u16 sp, pc;
} cpu_registers;

class cpu_context {
    cpu_registers regs;
    u16 fetch_data;
    u16 mem_dest;
    bool dest_is_mem;
    u8 current_opcode;
    instruction current_instruction;
    bool halted;
    bool stepping;
};

void cpu_init();
void cpu_step();
void fetch_instruction();
void execute_instruction();
void fetch_data();
u16 reverse(u16 num);
u16 cpu_read_register(register_type reg);