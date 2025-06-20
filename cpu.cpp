#include "gb_utils.hpp"

class CPU {
    private:
        u8 A, F, B, C, D, E, H, L;
        u16 SP, PC;

        const u8 ZERO_FLAG = 0x80;
        const u8 SUBTRACT_FLAG = 0x40;
        const u8 HALF_CARRY_FLAG = 0x20;
        const u8 CARRY_FLAG = 0x10;

    public:

