#include "../../include/instructions.hpp"

Instruction instructions[256];
void init_instructions() {
    instructions[0x00] = Instruction{INST_TYPE::IN_NOP, ADDR_MODE::AM_IMP};
    instructions[0x01] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_D16, REG_TYPE::RT_BC};
    instructions[0x02] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R, REG_TYPE::RT_BC, REG_TYPE::RT_A};
    instructions[0x03] = Instruction{INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_BC};
    instructions[0x04] = Instruction{INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_B};
    instructions[0x05] = Instruction{INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_B};
    instructions[0x06] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_B};
    instructions[0x07] = Instruction{INST_TYPE::IN_RLCA};
    instructions[0x08] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_A16_R, REG_TYPE::RT_NONE, REG_TYPE::RT_SP};
    instructions[0x09] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_HL, REG_TYPE::RT_BC};
    instructions[0x0A] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_BC};
    instructions[0x0B] = Instruction{INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_BC};
    instructions[0x0C] = Instruction{INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_C};
    instructions[0x0D] = Instruction{INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_C};
    instructions[0x0E] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_C};
    instructions[0x0F] = Instruction{INST_TYPE::IN_RRCA};
    instructions[0x10] = Instruction{INST_TYPE::IN_STOP, ADDR_MODE::AM_IMP};
    instructions[0x11] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_D16, REG_TYPE::RT_DE};
    instructions[0x12] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R, REG_TYPE::RT_DE, REG_TYPE::RT_A};
    instructions[0x13] = Instruction{INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_DE};
    instructions[0x14] = Instruction{INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_D};
    instructions[0x15] = Instruction{INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_D};
    instructions[0x16] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_D};
    instructions[0x17] = Instruction{INST_TYPE::IN_RLA};
    instructions[0x18] = Instruction{INST_TYPE::IN_JR, ADDR_MODE::AM_D8};
    instructions[0x19] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_HL, REG_TYPE::RT_DE};
    instructions[0x1A] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_DE};
    instructions[0x1B] = Instruction{INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_DE};
    instructions[0x1C] = Instruction{INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_E};
    instructions[0x1D] = Instruction{INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_E};
    instructions[0x1E] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_E};
    instructions[0x1F] = Instruction{INST_TYPE::IN_RRA};
    instructions[0x20] = Instruction{INST_TYPE::IN_JR, ADDR_MODE::AM_D8, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NZ};
    instructions[0x21] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_D16, REG_TYPE::RT_HL};
    instructions[0x22] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_HLI_R, REG_TYPE::RT_HL, REG_TYPE::RT_A};
    instructions[0x23] = Instruction{INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_HL};
    instructions[0x24] = Instruction{INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_H};
    instructions[0x25] = Instruction{INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_H};
    instructions[0x26] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_H};
    instructions[0x27] = Instruction{INST_TYPE::IN_DAA};
    instructions[0x28] = Instruction{INST_TYPE::IN_JR, ADDR_MODE::AM_D8, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_Z};
    instructions[0x29] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_HL, REG_TYPE::RT_HL};
    instructions[0x2A] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_HLI, REG_TYPE::RT_A, REG_TYPE::RT_HL};
    instructions[0x2B] = Instruction{INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_HL};
    instructions[0x2C] = Instruction{INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_L};
    instructions[0x2D] = Instruction{INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_L};
    instructions[0x2E] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_L};
    instructions[0x2F] = Instruction{INST_TYPE::IN_CPL};
    instructions[0x30] = Instruction{INST_TYPE::IN_JR, ADDR_MODE::AM_D8, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NC};
    instructions[0x31] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_D16, REG_TYPE::RT_SP};
    instructions[0x32] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_HLD_R, REG_TYPE::RT_HL, REG_TYPE::RT_A};
    instructions[0x33] = Instruction{INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_SP};
    instructions[0x34] = Instruction{INST_TYPE::IN_INC, ADDR_MODE::AM_MR, REG_TYPE::RT_HL};
    instructions[0x35] = Instruction{INST_TYPE::IN_DEC, ADDR_MODE::AM_MR, REG_TYPE::RT_HL};
    instructions[0x36] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_MR_D8, REG_TYPE::RT_HL};
    instructions[0x37] = Instruction{INST_TYPE::IN_SCF};
    instructions[0x38] = Instruction{INST_TYPE::IN_JR, ADDR_MODE::AM_D8, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_C};
    instructions[0x39] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_HL, REG_TYPE::RT_SP};
    instructions[0x3A] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_HLD, REG_TYPE::RT_A, REG_TYPE::RT_HL};
    instructions[0x3B] = Instruction{INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_SP};
    instructions[0x3C] = Instruction{INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_A};
    instructions[0x3D] = Instruction{INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_A};
    instructions[0x3E] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A};
    instructions[0x3F] = Instruction{INST_TYPE::IN_CCF};
    instructions[0x40] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_B};
    instructions[0x41] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_C};
    instructions[0x42] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_D};
    instructions[0x43] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_E};
    instructions[0x44] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_H};
    instructions[0x45] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_L};
    instructions[0x46] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_B, REG_TYPE::RT_HL};
    instructions[0x47] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_A};
    instructions[0x48] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_B};
    instructions[0x49] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_C};
    instructions[0x4A] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_D};
    instructions[0x4B] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_E};
    instructions[0x4C] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_H};
    instructions[0x4D] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_L};
    instructions[0x4E] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_C, REG_TYPE::RT_HL};
    instructions[0x4F] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_A};
    instructions[0x50] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_B};
    instructions[0x51] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_C};
    instructions[0x52] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_D};
    instructions[0x53] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_E};
    instructions[0x54] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_H};
    instructions[0x55] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_L};
    instructions[0x56] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_D, REG_TYPE::RT_HL};
    instructions[0x57] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_A};
    instructions[0x58] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_B};
    instructions[0x59] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_C};
    instructions[0x5A] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_D};
    instructions[0x5B] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_E};
    instructions[0x5C] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_H};
    instructions[0x5D] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_L};
    instructions[0x5E] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_E, REG_TYPE::RT_HL};
    instructions[0x5F] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_A};
    instructions[0x60] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_B};
    instructions[0x61] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_C};
    instructions[0x62] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_D};
    instructions[0x63] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_E};
    instructions[0x64] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_H};
    instructions[0x65] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_L};
    instructions[0x66] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_H, REG_TYPE::RT_HL};
    instructions[0x67] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_A};
    instructions[0x68] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_B};
    instructions[0x69] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_C};
    instructions[0x6A] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_D};
    instructions[0x6B] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_E};
    instructions[0x6C] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_H};
    instructions[0x6D] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_L};
    instructions[0x6E] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_L, REG_TYPE::RT_HL};
    instructions[0x6F] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_A};
    instructions[0x70] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_B};
    instructions[0x71] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_C};
    instructions[0x72] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_D};
    instructions[0x73] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_E};
    instructions[0x74] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_H};
    instructions[0x75] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_L};
    instructions[0x76] = Instruction{INST_TYPE::IN_HALT};
    instructions[0x77] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_A};
    instructions[0x78] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_B};
    instructions[0x79] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_C};
    instructions[0x7A] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_D};
    instructions[0x7B] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_E};
    instructions[0x7C] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_H};
    instructions[0x7D] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_L};
    instructions[0x7E] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL};
    instructions[0x7F] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_A};
    instructions[0x80] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B};
    instructions[0x81] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C};
    instructions[0x82] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D};
    instructions[0x83] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E};
    instructions[0x84] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H};
    instructions[0x85] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L};
    instructions[0x86] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL};
    instructions[0x87] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A};
    instructions[0x88] = Instruction{INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B};
    instructions[0x89] = Instruction{INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C};
    instructions[0x8A] = Instruction{INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D};
    instructions[0x8B] = Instruction{INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E};
    instructions[0x8C] = Instruction{INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H};
    instructions[0x8D] = Instruction{INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L};
    instructions[0x8E] = Instruction{INST_TYPE::IN_ADC, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL};
    instructions[0x8F] = Instruction{INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A};
    instructions[0x90] = Instruction{INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B};
    instructions[0x91] = Instruction{INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C};
    instructions[0x92] = Instruction{INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D};
    instructions[0x93] = Instruction{INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E};
    instructions[0x94] = Instruction{INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H};
    instructions[0x95] = Instruction{INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L};
    instructions[0x96] = Instruction{INST_TYPE::IN_SUB, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL};
    instructions[0x97] = Instruction{INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A};
    instructions[0x98] = Instruction{INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B};
    instructions[0x99] = Instruction{INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C};
    instructions[0x9A] = Instruction{INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D};
    instructions[0x9B] = Instruction{INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E};
    instructions[0x9C] = Instruction{INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H};
    instructions[0x9D] = Instruction{INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L};
    instructions[0x9E] = Instruction{INST_TYPE::IN_SBC, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL};
    instructions[0x9F] = Instruction{INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A};
    instructions[0xA0] = Instruction{INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B};
    instructions[0xA1] = Instruction{INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C};
    instructions[0xA2] = Instruction{INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D};
    instructions[0xA3] = Instruction{INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E};
    instructions[0xA4] = Instruction{INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H};
    instructions[0xA5] = Instruction{INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L};
    instructions[0xA6] = Instruction{INST_TYPE::IN_AND, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL};
    instructions[0xA7] = Instruction{INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A};
    instructions[0xA8] = Instruction{INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B};
    instructions[0xA9] = Instruction{INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C};
    instructions[0xAA] = Instruction{INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D};
    instructions[0xAB] = Instruction{INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E};
    instructions[0xAC] = Instruction{INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H};
    instructions[0xAD] = Instruction{INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L};
    instructions[0xAE] = Instruction{INST_TYPE::IN_XOR, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL};
    instructions[0xAF] = Instruction{INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A};
    instructions[0xB0] = Instruction{INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B};
    instructions[0xB1] = Instruction{INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C};
    instructions[0xB2] = Instruction{INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D};
    instructions[0xB3] = Instruction{INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E};
    instructions[0xB4] = Instruction{INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H};
    instructions[0xB5] = Instruction{INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L};
    instructions[0xB6] = Instruction{INST_TYPE::IN_OR, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL};
    instructions[0xB7] = Instruction{INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A};
    instructions[0xB8] = Instruction{INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B};
    instructions[0xB9] = Instruction{INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C};
    instructions[0xBA] = Instruction{INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D};
    instructions[0xBB] = Instruction{INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E};
    instructions[0xBC] = Instruction{INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H};
    instructions[0xBD] = Instruction{INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L};
    instructions[0xBE] = Instruction{INST_TYPE::IN_CP, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL};
    instructions[0xBF] = Instruction{INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A};
    instructions[0xC0] = Instruction{INST_TYPE::IN_RET, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NZ};
    instructions[0xC1] = Instruction{INST_TYPE::IN_POP, ADDR_MODE::AM_R, REG_TYPE::RT_BC};
    instructions[0xC2] = Instruction{INST_TYPE::IN_JP, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NZ};
    instructions[0xC3] = Instruction{INST_TYPE::IN_JP, ADDR_MODE::AM_D16};
    instructions[0xC4] = Instruction{INST_TYPE::IN_CALL, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NZ};
    instructions[0xC5] = Instruction{INST_TYPE::IN_PUSH, ADDR_MODE::AM_R, REG_TYPE::RT_BC};
    instructions[0xC6] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A};
    instructions[0xC7] = Instruction{INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x00};
    instructions[0xC8] = Instruction{INST_TYPE::IN_RET, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_Z};
    instructions[0xC9] = Instruction{INST_TYPE::IN_RET};
    instructions[0xCA] = Instruction{INST_TYPE::IN_JP, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_Z};
    instructions[0xCB] = Instruction{INST_TYPE::IN_CB, ADDR_MODE::AM_D8};
    instructions[0xCC] = Instruction{INST_TYPE::IN_CALL, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_Z};
    instructions[0xCD] = Instruction{INST_TYPE::IN_CALL, ADDR_MODE::AM_D16};
    instructions[0xCE] = Instruction{INST_TYPE::IN_ADC, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A};
    instructions[0xCF] = Instruction{INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x08};
    instructions[0xD0] = Instruction{INST_TYPE::IN_RET, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NC};
    instructions[0xD1] = Instruction{INST_TYPE::IN_POP, ADDR_MODE::AM_R, REG_TYPE::RT_DE};
    instructions[0xD2] = Instruction{INST_TYPE::IN_JP, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NC};
    instructions[0xD4] = Instruction{INST_TYPE::IN_CALL, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NC};
    instructions[0xD5] = Instruction{INST_TYPE::IN_PUSH, ADDR_MODE::AM_R, REG_TYPE::RT_DE};
    instructions[0xD6] = Instruction{INST_TYPE::IN_SUB, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A};
    instructions[0xD7] = Instruction{INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x10};
    instructions[0xD8] = Instruction{INST_TYPE::IN_RET, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_C};
    instructions[0xD9] = Instruction{INST_TYPE::IN_RETI};
    instructions[0xDA] = Instruction{INST_TYPE::IN_JP, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_C};
    instructions[0xDC] = Instruction{INST_TYPE::IN_CALL, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_C};
    instructions[0xDE] = Instruction{INST_TYPE::IN_SBC, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A};
    instructions[0xDF] = Instruction{INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x18};
    instructions[0xE0] = Instruction{INST_TYPE::IN_LDH, ADDR_MODE::AM_A8_R, REG_TYPE::RT_NONE, REG_TYPE::RT_A};
    instructions[0xE1] = Instruction{INST_TYPE::IN_POP, ADDR_MODE::AM_R, REG_TYPE::RT_HL};
    instructions[0xE2] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R, REG_TYPE::RT_C, REG_TYPE::RT_A};
    instructions[0xE5] = Instruction{INST_TYPE::IN_PUSH, ADDR_MODE::AM_R, REG_TYPE::RT_HL};
    instructions[0xE6] = Instruction{INST_TYPE::IN_AND, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A};
    instructions[0xE7] = Instruction{INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x20};
    instructions[0xE8] = Instruction{INST_TYPE::IN_ADD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_SP};
    instructions[0xE9] = Instruction{INST_TYPE::IN_JP, ADDR_MODE::AM_R, REG_TYPE::RT_HL};
    instructions[0xEA] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_A16_R, REG_TYPE::RT_NONE, REG_TYPE::RT_A};
    instructions[0xEE] = Instruction{INST_TYPE::IN_XOR, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A};
    instructions[0xEF] = Instruction{INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x28};
    instructions[0xF0] = Instruction{INST_TYPE::IN_LDH, ADDR_MODE::AM_R_A8, REG_TYPE::RT_A};
    instructions[0xF1] = Instruction{INST_TYPE::IN_POP, ADDR_MODE::AM_R, REG_TYPE::RT_AF};
    instructions[0xF2] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_C};
    instructions[0xF3] = Instruction{INST_TYPE::IN_DI};
    instructions[0xF5] = Instruction{INST_TYPE::IN_PUSH, ADDR_MODE::AM_R, REG_TYPE::RT_AF};
    instructions[0xF6] = Instruction{INST_TYPE::IN_OR, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A};
    instructions[0xF7] = Instruction{INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x30};
    instructions[0xF8] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_HL_SPR, REG_TYPE::RT_HL, REG_TYPE::RT_SP};
    instructions[0xF9] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_SP, REG_TYPE::RT_HL};
    instructions[0xFA] = Instruction{INST_TYPE::IN_LD, ADDR_MODE::AM_R_A16, REG_TYPE::RT_A};
    instructions[0xFB] = Instruction{INST_TYPE::IN_EI};
    instructions[0xFE] = Instruction{INST_TYPE::IN_CP, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A};
    instructions[0xFF] = Instruction{INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x38};
};

        // case 0x21:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_D16;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     break;

        // case 0x22:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_HLI_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x23:
        //     current_instruction.type = INST_TYPE::IN_INC;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     break;

        // case 0x24:
        //     current_instruction.type = INST_TYPE::IN_INC;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_H;
        //     break;

        // case 0x25:
        //     current_instruction.type = INST_TYPE::IN_DEC;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_H;
        //     break;

        // case 0x26:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_H;
        //     break;

        // case 0x27:
        //     current_instruction.type = INST_TYPE::IN_DAA;
        //     break;

        // case 0x28:
        //     current_instruction.type = INST_TYPE::IN_JR;
        //     current_instruction.mode = ADDR_MODE::AM_D8;
        //     current_instruction.condition = COND_TYPE::CT_Z;
        //     break;

        // case 0x29:
        //     current_instruction.type = INST_TYPE::IN_ADD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x2A:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_HLI;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x2B:
        //     current_instruction.type = INST_TYPE::IN_DEC;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     break;

        // case 0x2C:
        //     current_instruction.type = INST_TYPE::IN_INC;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_L;
        //     break;

        // case 0x2D:
        //     current_instruction.type = INST_TYPE::IN_DEC;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_L;
        //     break;

        // case 0x2E:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_L;
        //     break;

        // case 0x2F:
        //     current_instruction.type = INST_TYPE::IN_CPL;
        //     break;

        // case 0x30:
        //     current_instruction.type = INST_TYPE::IN_JR;
        //     current_instruction.mode = ADDR_MODE::AM_D8;
        //     current_instruction.condition = COND_TYPE::CT_NC;
        //     break;

        // case 0x31:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_D16;
        //     current_instruction.reg1 = REG_TYPE::RT_SP;
        //     break;
        // case 0x32:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_HLD_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x33:
        //     current_instruction.type = INST_TYPE::IN_INC;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_SP;
        //     break;

        // case 0x34:
        //     current_instruction.type = INST_TYPE::IN_INC;
        //     current_instruction.mode = ADDR_MODE::AM_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     break;

        // case 0x35:
        //     current_instruction.type = INST_TYPE::IN_DEC;
        //     current_instruction.mode = ADDR_MODE::AM_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     break;

        // case 0x36:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_MR_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     break;

        // case 0x37:
        //     current_instruction.type = INST_TYPE::IN_SCF;
        //     break;

        // case 0x38:
        //     current_instruction.type = INST_TYPE::IN_JR;
        //     current_instruction.mode = ADDR_MODE::AM_D8;
        //     current_instruction.condition = COND_TYPE::CT_C;
        //     break;

        // case 0x39:
        //     current_instruction.type = INST_TYPE::IN_ADD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     current_instruction.reg2 = REG_TYPE::RT_SP;
        //     break;

        // case 0x3A:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_HLD;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x3B:
        //     current_instruction.type = INST_TYPE::IN_DEC;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_SP;
        //     break;

        // case 0x3C:
        //     current_instruction.type = INST_TYPE::IN_INC;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0x3D:
        //     current_instruction.type = INST_TYPE::IN_DEC;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0x3E:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0x3F:
        //     current_instruction.type = INST_TYPE::IN_CCF;
        //     break;

        // case 0x40:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_B;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0x41:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_B;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0x42:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_B;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0x43:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_B;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0x44:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_B;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0x45:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_B;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0x46:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_B;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x47:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_B;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x48:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_C;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0x49:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_C;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0x4A:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_C;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0x4B:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_C;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0x4C:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_C;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0x4D:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_C;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0x4E:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_C;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x4F:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_C;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x50:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_D;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0x51:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_D;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0x52:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_D;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0x53:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_D;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0x54:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_D;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0x55:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_D;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0x56:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_D;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x57:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_D;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x58:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_E;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0x59:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_E;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0x5A:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_E;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0x5B:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_E;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0x5C:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_E;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0x5D:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_E;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0x5E:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_E;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x5F:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_E;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x60:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_H;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0x61:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_H;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0x62:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_H;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0x63:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_H;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;
        // case 0x64:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_H;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0x65:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_H;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0x66:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_H;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x67:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_H;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x68:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_L;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0x69:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_L;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0x6A:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_L;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0x6B:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_L;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0x6C:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_L;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0x6D:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_L;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0x6E:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_L;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x6F:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_L;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x70:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_MR_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0x71:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_MR_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0x72:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_MR_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0x73:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_MR_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0x74:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_MR_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0x75:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_MR_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0x76:
        //     current_instruction.type = INST_TYPE::IN_HALT;
        //     break;

        // case 0x77:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_MR_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x78:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0x79:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0x7A:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0x7B:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0x7C:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0x7D:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0x7E:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x7F:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x80:
        //     current_instruction.type = INST_TYPE::IN_ADD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0x81:
        //     current_instruction.type = INST_TYPE::IN_ADD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0x82:
        //     current_instruction.type = INST_TYPE::IN_ADD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0x83:
        //     current_instruction.type = INST_TYPE::IN_ADD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0x84:
        //     current_instruction.type = INST_TYPE::IN_ADD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0x85:
        //     current_instruction.type = INST_TYPE::IN_ADD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0x86:
        //     current_instruction.type = INST_TYPE::IN_ADD;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x87:
        //     current_instruction.type = INST_TYPE::IN_ADD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x88:
        //     current_instruction.type = INST_TYPE::IN_ADC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0x89:
        //     current_instruction.type = INST_TYPE::IN_ADC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0x8A:
        //     current_instruction.type = INST_TYPE::IN_ADC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0x8B:
        //     current_instruction.type = INST_TYPE::IN_ADC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0x8C:
        //     current_instruction.type = INST_TYPE::IN_ADC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0x8D:
        //     current_instruction.type = INST_TYPE::IN_ADC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0x8E:
        //     current_instruction.type = INST_TYPE::IN_ADC;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x8F:
        //     current_instruction.type = INST_TYPE::IN_ADC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x90:
        //     current_instruction.type = INST_TYPE::IN_SUB;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_B;
        //     break;

        // case 0x91:
        //     current_instruction.type = INST_TYPE::IN_SUB;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_C;
        //     break;

        // case 0x92:
        //     current_instruction.type = INST_TYPE::IN_SUB;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_D;
        //     break;

        // case 0x93:
        //     current_instruction.type = INST_TYPE::IN_SUB;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_E;
        //     break;

        // case 0x94:
        //     current_instruction.type = INST_TYPE::IN_SUB;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_H;
        //     break;

        // case 0x95:
        //     current_instruction.type = INST_TYPE::IN_SUB;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_L;
        //     break;
        // case 0x96:
        //     current_instruction.type = INST_TYPE::IN_SUB;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x97:
        //     current_instruction.type = INST_TYPE::IN_SUB;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0x98:
        //     current_instruction.type = INST_TYPE::IN_SBC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0x99:
        //     current_instruction.type = INST_TYPE::IN_SBC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0x9A:
        //     current_instruction.type = INST_TYPE::IN_SBC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0x9B:
        //     current_instruction.type = INST_TYPE::IN_SBC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0x9C:
        //     current_instruction.type = INST_TYPE::IN_SBC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0x9D:
        //     current_instruction.type = INST_TYPE::IN_SBC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0x9E:
        //     current_instruction.type = INST_TYPE::IN_SBC;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0x9F:
        //     current_instruction.type = INST_TYPE::IN_SBC;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0xA0:
        //     current_instruction.type = INST_TYPE::IN_AND;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0xA1:
        //     current_instruction.type = INST_TYPE::IN_AND;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0xA2:
        //     current_instruction.type = INST_TYPE::IN_AND;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0xA3:
        //     current_instruction.type = INST_TYPE::IN_AND;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0xA4:
        //     current_instruction.type = INST_TYPE::IN_AND;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0xA5:
        //     current_instruction.type = INST_TYPE::IN_AND;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0xA6:
        //     current_instruction.type = INST_TYPE::IN_AND;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0xA7:
        //     current_instruction.type = INST_TYPE::IN_AND;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0xA8:
        //     current_instruction.type = INST_TYPE::IN_XOR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0xA9:
        //     current_instruction.type = INST_TYPE::IN_XOR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0xAA:
        //     current_instruction.type = INST_TYPE::IN_XOR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0xAB:
        //     current_instruction.type = INST_TYPE::IN_XOR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0xAC:
        //     current_instruction.type = INST_TYPE::IN_XOR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0xAD:
        //     current_instruction.type = INST_TYPE::IN_XOR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0xAE:
        //     current_instruction.type = INST_TYPE::IN_XOR;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0xAF:
        //     current_instruction.type = INST_TYPE::IN_XOR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0xB0:
        //     current_instruction.type = INST_TYPE::IN_OR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0xB1:
        //     current_instruction.type = INST_TYPE::IN_OR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0xB2:
        //     current_instruction.type = INST_TYPE::IN_OR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0xB3:
        //     current_instruction.type = INST_TYPE::IN_OR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0xB4:
        //     current_instruction.type = INST_TYPE::IN_OR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0xB5:
        //     current_instruction.type = INST_TYPE::IN_OR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0xB6:
        //     current_instruction.type = INST_TYPE::IN_OR;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0xB7:
        //     current_instruction.type = INST_TYPE::IN_OR;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0xB8:
        //     current_instruction.type = INST_TYPE::IN_CP;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_B;
        //     break;

        // case 0xB9:
        //     current_instruction.type = INST_TYPE::IN_CP;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0xBA:
        //     current_instruction.type = INST_TYPE::IN_CP;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_D;
        //     break;

        // case 0xBB:
        //     current_instruction.type = INST_TYPE::IN_CP;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_E;
        //     break;

        // case 0xBC:
        //     current_instruction.type = INST_TYPE::IN_CP;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_H;
        //     break;

        // case 0xBD:
        //     current_instruction.type = INST_TYPE::IN_CP;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_L;
        //     break;

        // case 0xBE:
        //     current_instruction.type = INST_TYPE::IN_CP;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0xBF:
        //     current_instruction.type = INST_TYPE::IN_CP;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0xC0:
        //     current_instruction.type = INST_TYPE::IN_RET;
        //     current_instruction.mode = ADDR_MODE::AM_IMP;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NZ;
        //     break;

        // case 0xC1:
        //     current_instruction.type = INST_TYPE::IN_POP;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_BC;
        //     break;

        // case 0xC2:
        //     current_instruction.type = INST_TYPE::IN_JP;
        //     current_instruction.mode = ADDR_MODE::AM_D16;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NZ;
        //     break;

        // case 0xC3:
        //     current_instruction.type = INST_TYPE::IN_JP;
        //     current_instruction.mode = ADDR_MODE::AM_D16;
        //     break;

        // case 0xC4:
        //     current_instruction.type = INST_TYPE::IN_CALL;
        //     current_instruction.mode = ADDR_MODE::AM_D16;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NZ;
        //     break;

        // case 0xC5:
        //     current_instruction.type = INST_TYPE::IN_PUSH;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_BC;
        //     break;

        // case 0xC6:
        //     current_instruction.type = INST_TYPE::IN_ADD;
        //     current_instruction.mode = ADDR_MODE::AM_R_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0xC7:
        //     current_instruction.type = INST_TYPE::IN_RST;
        //     current_instruction.mode = ADDR_MODE::AM_IMP;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NONE;
        //     current_instruction.param = 0x00;
        //     break;
        // case 0xC8:
        //     current_instruction.type = INST_TYPE::IN_RET;
        //     current_instruction.mode = ADDR_MODE::AM_IMP;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_Z;
        //     break;

        // case 0xC9:
        //     current_instruction.type = INST_TYPE::IN_RET;
        //     break;

        // case 0xCA:
        //     current_instruction.type = INST_TYPE::IN_JP;
        //     current_instruction.mode = ADDR_MODE::AM_D16;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_Z;
        //     break;

        // case 0xCB:
        //     current_instruction.type = INST_TYPE::IN_CB;
        //     current_instruction.mode = ADDR_MODE::AM_D8;
        //     break;

        // case 0xCC:
        //     current_instruction.type = INST_TYPE::IN_CALL;
        //     current_instruction.mode = ADDR_MODE::AM_D16;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_Z;
        //     break;

        // case 0xCD:
        //     current_instruction.type = INST_TYPE::IN_CALL;
        //     current_instruction.mode = ADDR_MODE::AM_D16;
        //     break;

        // case 0xCE:
        //     current_instruction.type = INST_TYPE::IN_ADC;
        //     current_instruction.mode = ADDR_MODE::AM_R_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0xCF:
        //     current_instruction.type = INST_TYPE::IN_RST;
        //     current_instruction.mode = ADDR_MODE::AM_IMP;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NONE;
        //     current_instruction.param = 0x08;
        //     break;

        // case 0xD0:
        //     current_instruction.type = INST_TYPE::IN_RET;
        //     current_instruction.mode = ADDR_MODE::AM_IMP;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NC;
        //     break;

        // case 0xD1:
        //     current_instruction.type = INST_TYPE::IN_POP;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_DE;
        //     break;

        // case 0xD2:
        //     current_instruction.type = INST_TYPE::IN_JP;
        //     current_instruction.mode = ADDR_MODE::AM_D16;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NC;
        //     break;

        // case 0xD4:
        //     current_instruction.type = INST_TYPE::IN_CALL;
        //     current_instruction.mode = ADDR_MODE::AM_D16;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NC;
        //     break;

        // case 0xD5:
        //     current_instruction.type = INST_TYPE::IN_PUSH;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_DE;
        //     break;

        // case 0xD6:
        //     current_instruction.type = INST_TYPE::IN_SUB;
        //     current_instruction.mode = ADDR_MODE::AM_R_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0xD7:
        //     current_instruction.type = INST_TYPE::IN_RST;
        //     current_instruction.mode = ADDR_MODE::AM_IMP;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NONE;
        //     current_instruction.param = 0x10;
        //     break;

        // case 0xD8:
        //     current_instruction.type = INST_TYPE::IN_RET;
        //     current_instruction.mode = ADDR_MODE::AM_IMP;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_C;
        //     break;

        // case 0xD9:
        //     current_instruction.type = INST_TYPE::IN_RETI;
        //     break;

        // case 0xDA:
        //     current_instruction.type = INST_TYPE::IN_JP;
        //     current_instruction.mode = ADDR_MODE::AM_D16;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_C;
        //     break;

        // case 0xDC:
        //     current_instruction.type = INST_TYPE::IN_CALL;
        //     current_instruction.mode = ADDR_MODE::AM_D16;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_C;
        //     break;

        // case 0xDE:
        //     current_instruction.type = INST_TYPE::IN_SBC;
        //     current_instruction.mode = ADDR_MODE::AM_R_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0xDF:
        //     current_instruction.type = INST_TYPE::IN_RST;
        //     current_instruction.mode = ADDR_MODE::AM_IMP;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NONE;
        //     current_instruction.param = 0x18;
        //     break;
        // case 0xE0:
        //     current_instruction.type = INST_TYPE::IN_LDH;
        //     current_instruction.mode = ADDR_MODE::AM_A8_R;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0xE1:
        //     current_instruction.type = INST_TYPE::IN_POP;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     break;

        // case 0xE2:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_MR_R;
        //     current_instruction.reg1 = REG_TYPE::RT_C;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0xE5:
        //     current_instruction.type = INST_TYPE::IN_PUSH;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     break;

        // case 0xE6:
        //     current_instruction.type = INST_TYPE::IN_AND;
        //     current_instruction.mode = ADDR_MODE::AM_R_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0xE7:
        //     current_instruction.type = INST_TYPE::IN_RST;
        //     current_instruction.mode = ADDR_MODE::AM_IMP;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NONE;
        //     current_instruction.param = 0x20;
        //     break;

        // case 0xE8:
        //     current_instruction.type = INST_TYPE::IN_ADD;
        //     current_instruction.mode = ADDR_MODE::AM_R_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_SP;
        //     break;

        // case 0xE9:
        //     current_instruction.type = INST_TYPE::IN_JP;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     break;

        // case 0xEA:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_A16_R;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_A;
        //     break;

        // case 0xEE:
        //     current_instruction.type = INST_TYPE::IN_XOR;
        //     current_instruction.mode = ADDR_MODE::AM_R_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0xEF:
        //     current_instruction.type = INST_TYPE::IN_RST;
        //     current_instruction.mode = ADDR_MODE::AM_IMP;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NONE;
        //     current_instruction.param = 0x28;
        //     break;

        // case 0xF0:
        //     current_instruction.type = INST_TYPE::IN_LDH;
        //     current_instruction.mode = ADDR_MODE::AM_R_A8;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0xF1:
        //     current_instruction.type = INST_TYPE::IN_POP;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_AF;
        //     break;

        // case 0xF2:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_MR;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     current_instruction.reg2 = REG_TYPE::RT_C;
        //     break;

        // case 0xF3:
        //     current_instruction.type = INST_TYPE::IN_DI;
        //     break;

        // case 0xF5:
        //     current_instruction.type = INST_TYPE::IN_PUSH;
        //     current_instruction.mode = ADDR_MODE::AM_R;
        //     current_instruction.reg1 = REG_TYPE::RT_AF;
        //     break;

        // case 0xF6:
        //     current_instruction.type = INST_TYPE::IN_OR;
        //     current_instruction.mode = ADDR_MODE::AM_R_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0xF7:
        //     current_instruction.type = INST_TYPE::IN_RST;
        //     current_instruction.mode = ADDR_MODE::AM_IMP;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NONE;
        //     current_instruction.param = 0x30;
        //     break;
        // case 0xF8:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_HL_SPR;
        //     current_instruction.reg1 = REG_TYPE::RT_HL;
        //     current_instruction.reg2 = REG_TYPE::RT_SP;
        //     break;

        // case 0xF9:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_R;
        //     current_instruction.reg1 = REG_TYPE::RT_SP;
        //     current_instruction.reg2 = REG_TYPE::RT_HL;
        //     break;

        // case 0xFA:
        //     current_instruction.type = INST_TYPE::IN_LD;
        //     current_instruction.mode = ADDR_MODE::AM_R_A16;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0xFB:
        //     current_instruction.type = INST_TYPE::IN_EI;
        //     break;

        // case 0xFE:
        //     current_instruction.type = INST_TYPE::IN_CP;
        //     current_instruction.mode = ADDR_MODE::AM_R_D8;
        //     current_instruction.reg1 = REG_TYPE::RT_A;
        //     break;

        // case 0xFF:
        //     current_instruction.type = INST_TYPE::IN_RST;
        //     current_instruction.mode = ADDR_MODE::AM_IMP;
        //     current_instruction.reg1 = REG_TYPE::RT_NONE;
        //     current_instruction.reg2 = REG_TYPE::RT_NONE;
        //     current_instruction.condition = COND_TYPE::CT_NONE;
        //     current_instruction.param = 0x38;
        //     break;