#include "gb_utils.hpp"
#include "cpu.hpp"

extern cpu_context cctx;

u16 reverse(u16 num) {
    return ((num & 0x00FF) << 8) | ((num & 0xFF00) >> 8);
}

u16 cpu_read_register(register_type reg) {
    switch (reg) {
        case register_type::RT_A: return cctx.regs.a;
        case register_type::RT_F: return cctx.regs.f;
        case register_type::RT_B: return cctx.regs.b;
        case register_type::RT_C: return cctx.regs.c;
        case register_type::RT_D: return cctx.regs.d;
        case register_type::RT_E: return cctx.regs.e;
        case register_type::RT_H: return cctx.regs.h;
        case register_type::RT_L: return cctx.regs.l;

        case register_type::RT_AF: return reverse(*((u16*)&cctx.regs.a));
        case register_type::RT_BC: return reverse(*((u16*)&cctx.regs.b));
        case register_type::RT_DE: return reverse(*((u16*)&cctx.regs.d));
        case register_type::RT_HL: return reverse(*((u16*)&cctx.regs.h));

        case register_type::RT_SP: return cctx.regs.sp;
        case register_type::RT_PC: return cctx.regs.pc;
        default:
            cout << "Error: Invalid register type " << static_cast<int>(reg) << endl;
            return -1;
    }
}