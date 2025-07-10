#include "../../include/cpu.hpp"

uint16_t RegisterFile::read_register(REG_TYPE reg) {
    auto get16 = [&](auto high_reg, auto low_reg) -> uint16_t {
        return (high_reg << 8) | low_reg;
    };

    switch (reg) {
        case REG_TYPE::RT_A: return _a;
        case REG_TYPE::RT_F: return flags.get_byte();
        case REG_TYPE::RT_B: return _b;
        case REG_TYPE::RT_C: return _c;
        case REG_TYPE::RT_D: return _d;
        case REG_TYPE::RT_E: return _e;
        case REG_TYPE::RT_H: return _h;
        case REG_TYPE::RT_L: return _l;

        case REG_TYPE::RT_AF: return get16(_a, flags.get_byte());
        case REG_TYPE::RT_BC: return get16(_b, _c);
        case REG_TYPE::RT_DE: return get16(_d, _e);
        case REG_TYPE::RT_HL: return get16(_h, _l);

        case REG_TYPE::RT_PC: return PC;
        case REG_TYPE::RT_SP: return SP;

        case REG_TYPE::RT_NONE: return 0;
    }
}

void RegisterFile::set_register(REG_TYPE reg, uint16_t value) {
    auto set16 = [&](auto& high_reg, auto& low_reg) {
        high_reg = (value >> 8);
        low_reg = (value & 0xFF);
    };

    switch (reg) {
        case REG_TYPE::RT_A: _a = value & 0xFF; break;
        case REG_TYPE::RT_B: _b = value & 0xFF; break;
        case REG_TYPE::RT_C: _c = value & 0xFF; break;
        case REG_TYPE::RT_D: _d = value & 0xFF; break;
        case REG_TYPE::RT_E: _e = value & 0xFF; break;
        case REG_TYPE::RT_H: _h = value & 0xFF; break;
        case REG_TYPE::RT_L: _l = value & 0xFF; break;
        case REG_TYPE::RT_F: flags = (value & 0xFF); break;

        case REG_TYPE::RT_AF: set16(_a, flags); break;
        case REG_TYPE::RT_BC: set16(_b, _c); break;
        case REG_TYPE::RT_DE: set16(_d, _e); break;
        case REG_TYPE::RT_HL: set16(_h, _l); break;

        case REG_TYPE::RT_SP: SP = value; break;
        case REG_TYPE::RT_PC: PC = value; break;

        case REG_TYPE::RT_NONE: break;
    }
}
