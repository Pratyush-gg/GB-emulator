#include "instructions.hpp"
#include "cpu.hpp"

instruction instructions[] = {
    {0x00, "NOP", address_mode::AM_IMP, register_type::RT_NONE, instruction_type::IN_NOP},
    {0x01, "LD BC, d16", address_mode::AM_R_D16, register_type::RT_BC, instruction_type::IN_LD},
    {0x02, "LD (BC), A", address_mode::AM_MR_R, register_type::RT_A, instruction_type::IN_LD},
    {0x03, "INC BC", address_mode::AM_R, register_type::RT_BC, instruction_type::IN_INC},
    {0x04, "INC B", address_mode::AM_R, register_type::RT_B, instruction_type::IN_INC},
    {0x05, "DEC B", address_mode::AM_R, register_type::RT_B, instruction_type::IN_DEC},
    {0x06, "LD B, d8", address_mode::AM_R_D8, register_type::RT_B, instruction_type::IN_LD},
    {0x07, "RLCA", address_mode::AM_IMP, register_type::RT_NONE, instruction_type::IN_RLCA},
    // .(rest of the instructions) (AI generated check!!)
};