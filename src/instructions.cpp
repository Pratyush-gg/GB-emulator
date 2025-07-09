#include "../include/instructions.hpp"

Instruction instructions[256] = {
    [0x00] = {INST_TYPE::IN_NOP, ADDR_MODE::AM_IMP},
    [0x01] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_D16, REG_TYPE::RT_BC},
    [0x02] = {INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R, REG_TYPE::RT_BC, REG_TYPE::RT_A},
    [0x03] = {INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_BC},
    [0x04] = {INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_B},
    [0x05] = {INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_B},
    [0x06] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_B},
    [0x07] = {INST_TYPE::IN_RLCA},
    [0x08] = {INST_TYPE::IN_LD, ADDR_MODE::AM_A16_R, REG_TYPE::RT_NONE, REG_TYPE::RT_SP},
    [0x09] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_HL, REG_TYPE::RT_BC},
    [0x0A] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_BC},
    [0x0B] = {INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_BC},
    [0x0C] = {INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_C},
    [0x0D] = {INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_C},
    [0x0E] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_C},
    [0x0F] = {INST_TYPE::IN_RRCA},
    [0x10] = {INST_TYPE::IN_STOP, ADDR_MODE::AM_IMP},
    [0x11] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_D16, REG_TYPE::RT_DE},
    [0x12] = {INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R, REG_TYPE::RT_DE, REG_TYPE::RT_A},
    [0x13] = {INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_DE},
    [0x14] = {INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_D},
    [0x15] = {INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_D},
    [0x16] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_D},
    [0x17] = {INST_TYPE::IN_RLA},
    [0x18] = {INST_TYPE::IN_JR, ADDR_MODE::AM_D8},
    [0x19] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_HL, REG_TYPE::RT_DE},
    [0x1A] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_DE},
    [0x1B] = {INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_DE},
    [0x1C] = {INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_E},
    [0x1D] = {INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_E},
    [0x1E] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_E},
    [0x1F] = {INST_TYPE::IN_RRA},
    [0x20] = {INST_TYPE::IN_JR, ADDR_MODE::AM_D8, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NZ},
    [0x21] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_D16, REG_TYPE::RT_HL},
    [0x22] = {INST_TYPE::IN_LD, ADDR_MODE::AM_HLI_R, REG_TYPE::RT_HL, REG_TYPE::RT_A},
    [0x23] = {INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_HL},
    [0x24] = {INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_H},
    [0x25] = {INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_H},
    [0x26] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_H},
    [0x27] = {INST_TYPE::IN_DAA},
    [0x28] = {INST_TYPE::IN_JR, ADDR_MODE::AM_D8, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_Z},
    [0x29] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_HL, REG_TYPE::RT_HL},
    [0x2A] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_HLI, REG_TYPE::RT_A, REG_TYPE::RT_HL},
    [0x2B] = {INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_HL},
    [0x2C] = {INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_L},
    [0x2D] = {INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_L},
    [0x2E] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_L},
    [0x2F] = {INST_TYPE::IN_CPL},
    [0x30] = {INST_TYPE::IN_JR, ADDR_MODE::AM_D8, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NC},
    [0x31] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_D16, REG_TYPE::RT_SP},
    [0x32] = {INST_TYPE::IN_LD, ADDR_MODE::AM_HLD_R, REG_TYPE::RT_HL, REG_TYPE::RT_A},
    [0x33] = {INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_SP},
    [0x34] = {INST_TYPE::IN_INC, ADDR_MODE::AM_MR, REG_TYPE::RT_HL},
    [0x35] = {INST_TYPE::IN_DEC, ADDR_MODE::AM_MR, REG_TYPE::RT_HL},
    [0x36] = {INST_TYPE::IN_LD, ADDR_MODE::AM_MR_D8, REG_TYPE::RT_HL},
    [0x37] = {INST_TYPE::IN_SCF},
    [0x38] = {INST_TYPE::IN_JR, ADDR_MODE::AM_D8, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_C},
    [0x39] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_HL, REG_TYPE::RT_SP},
    [0x3A] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_HLD, REG_TYPE::RT_A, REG_TYPE::RT_HL},
    [0x3B] = {INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_SP},
    [0x3C] = {INST_TYPE::IN_INC, ADDR_MODE::AM_R, REG_TYPE::RT_A},
    [0x3D] = {INST_TYPE::IN_DEC, ADDR_MODE::AM_R, REG_TYPE::RT_A},
    [0x3E] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A},
    [0x3F] = {INST_TYPE::IN_CCF},
    [0x40] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_B},
    [0x41] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_C},
    [0x42] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_D},
    [0x43] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_E},
    [0x44] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_H},
    [0x45] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_L},
    [0x46] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_B, REG_TYPE::RT_HL},
    [0x47] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_B, REG_TYPE::RT_A},
    [0x48] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_B},
    [0x49] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_C},
    [0x4A] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_D},
    [0x4B] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_E},
    [0x4C] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_H},
    [0x4D] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_L},
    [0x4E] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_C, REG_TYPE::RT_HL},
    [0x4F] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_C, REG_TYPE::RT_A},
    [0x50] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_B},
    [0x51] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_C},
    [0x52] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_D},
    [0x53] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_E},
    [0x54] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_H},
    [0x55] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_L},
    [0x56] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_D, REG_TYPE::RT_HL},
    [0x57] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_D, REG_TYPE::RT_A},
    [0x58] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_B},
    [0x59] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_C},
    [0x5A] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_D},
    [0x5B] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_E},
    [0x5C] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_H},
    [0x5D] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_L},
    [0x5E] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_E, REG_TYPE::RT_HL},
    [0x5F] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_E, REG_TYPE::RT_A},
    [0x60] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_B},
    [0x61] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_C},
    [0x62] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_D},
    [0x63] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_E},
    [0x64] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_H},
    [0x65] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_L},
    [0x66] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_H, REG_TYPE::RT_HL},
    [0x67] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_H, REG_TYPE::RT_A},
    [0x68] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_B},
    [0x69] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_C},
    [0x6A] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_D},
    [0x6B] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_E},
    [0x6C] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_H},
    [0x6D] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_L},
    [0x6E] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_L, REG_TYPE::RT_HL},
    [0x6F] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_L, REG_TYPE::RT_A},
    [0x70] = {INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_B},
    [0x71] = {INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_C},
    [0x72] = {INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_D},
    [0x73] = {INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_E},
    [0x74] = {INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_H},
    [0x75] = {INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_L},
    [0x76] = {INST_TYPE::IN_HALT},
    [0x77] = {INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R,  REG_TYPE::RT_HL, REG_TYPE::RT_A},
    [0x78] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_B},
    [0x79] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_C},
    [0x7A] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_D},
    [0x7B] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_E},
    [0x7C] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_H},
    [0x7D] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_L},
    [0x7E] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL},
    [0x7F] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R,  REG_TYPE::RT_A, REG_TYPE::RT_A},
    [0x80] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B},
    [0x81] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C},
    [0x82] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D},
    [0x83] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E},
    [0x84] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H},
    [0x85] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L},
    [0x86] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL},
    [0x87] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A},
    [0x88] = {INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B},
    [0x89] = {INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C},
    [0x8A] = {INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D},
    [0x8B] = {INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E},
    [0x8C] = {INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H},
    [0x8D] = {INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L},
    [0x8E] = {INST_TYPE::IN_ADC, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL},
    [0x8F] = {INST_TYPE::IN_ADC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A},
    [0x90] = {INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B},
    [0x91] = {INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C},
    [0x92] = {INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D},
    [0x93] = {INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E},
    [0x94] = {INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H},
    [0x95] = {INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L},
    [0x96] = {INST_TYPE::IN_SUB, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL},
    [0x97] = {INST_TYPE::IN_SUB, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A},
    [0x98] = {INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B},
    [0x99] = {INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C},
    [0x9A] = {INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D},
    [0x9B] = {INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E},
    [0x9C] = {INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H},
    [0x9D] = {INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L},
    [0x9E] = {INST_TYPE::IN_SBC, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL},
    [0x9F] = {INST_TYPE::IN_SBC, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A},
    [0xA0] = {INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B},
    [0xA1] = {INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C},
    [0xA2] = {INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D},
    [0xA3] = {INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E},
    [0xA4] = {INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H},
    [0xA5] = {INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L},
    [0xA6] = {INST_TYPE::IN_AND, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL},
    [0xA7] = {INST_TYPE::IN_AND, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A},
    [0xA8] = {INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B},
    [0xA9] = {INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C},
    [0xAA] = {INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D},
    [0xAB] = {INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E},
    [0xAC] = {INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H},
    [0xAD] = {INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L},
    [0xAE] = {INST_TYPE::IN_XOR, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL},
    [0xAF] = {INST_TYPE::IN_XOR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A},
    [0xB0] = {INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B},
    [0xB1] = {INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C},
    [0xB2] = {INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D},
    [0xB3] = {INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E},
    [0xB4] = {INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H},
    [0xB5] = {INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L},
    [0xB6] = {INST_TYPE::IN_OR, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL},
    [0xB7] = {INST_TYPE::IN_OR, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A},
    [0xB8] = {INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_B},
    [0xB9] = {INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_C},
    [0xBA] = {INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_D},
    [0xBB] = {INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_E},
    [0xBC] = {INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_H},
    [0xBD] = {INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_L},
    [0xBE] = {INST_TYPE::IN_CP, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_HL},
    [0xBF] = {INST_TYPE::IN_CP, ADDR_MODE::AM_R_R, REG_TYPE::RT_A, REG_TYPE::RT_A},
    [0xC0] = {INST_TYPE::IN_RET, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NZ},
    [0xC1] = {INST_TYPE::IN_POP, ADDR_MODE::AM_R, REG_TYPE::RT_BC},
    [0xC2] = {INST_TYPE::IN_JP, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NZ},
    [0xC3] = {INST_TYPE::IN_JP, ADDR_MODE::AM_D16},
    [0xC4] = {INST_TYPE::IN_CALL, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NZ},
    [0xC5] = {INST_TYPE::IN_PUSH, ADDR_MODE::AM_R, REG_TYPE::RT_BC},
    [0xC6] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A},
    [0xC7] = {INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x00},
    [0xC8] = {INST_TYPE::IN_RET, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_Z},
    [0xC9] = {INST_TYPE::IN_RET},
    [0xCA] = {INST_TYPE::IN_JP, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_Z},
    [0xCB] = {INST_TYPE::IN_CB, ADDR_MODE::AM_D8},
    [0xCC] = {INST_TYPE::IN_CALL, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_Z},
    [0xCD] = {INST_TYPE::IN_CALL, ADDR_MODE::AM_D16},
    [0xCE] = {INST_TYPE::IN_ADC, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A},
    [0xCF] = {INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x08},
    [0xD0] = {INST_TYPE::IN_RET, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NC},
    [0xD1] = {INST_TYPE::IN_POP, ADDR_MODE::AM_R, REG_TYPE::RT_DE},
    [0xD2] = {INST_TYPE::IN_JP, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NC},
    [0xD4] = {INST_TYPE::IN_CALL, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NC},
    [0xD5] = {INST_TYPE::IN_PUSH, ADDR_MODE::AM_R, REG_TYPE::RT_DE},
    [0xD6] = {INST_TYPE::IN_SUB, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A},
    [0xD7] = {INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x10},
    [0xD8] = {INST_TYPE::IN_RET, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_C},
    [0xD9] = {INST_TYPE::IN_RETI},
    [0xDA] = {INST_TYPE::IN_JP, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_C},
    [0xDC] = {INST_TYPE::IN_CALL, ADDR_MODE::AM_D16, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_C},
    [0xDE] = {INST_TYPE::IN_SBC, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A},
    [0xDF] = {INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x18},
    [0xE0] = {INST_TYPE::IN_LDH, ADDR_MODE::AM_A8_R, REG_TYPE::RT_NONE, REG_TYPE::RT_A},
    [0xE1] = {INST_TYPE::IN_POP, ADDR_MODE::AM_R, REG_TYPE::RT_HL},
    [0xE2] = {INST_TYPE::IN_LD, ADDR_MODE::AM_MR_R, REG_TYPE::RT_C, REG_TYPE::RT_A},
    [0xE5] = {INST_TYPE::IN_PUSH, ADDR_MODE::AM_R, REG_TYPE::RT_HL},
    [0xE6] = {INST_TYPE::IN_AND, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A},
    [0xE7] = {INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x20},
    [0xE8] = {INST_TYPE::IN_ADD, ADDR_MODE::AM_R_D8, REG_TYPE::RT_SP},
    [0xE9] = {INST_TYPE::IN_JP, ADDR_MODE::AM_R, REG_TYPE::RT_HL},
    [0xEA] = {INST_TYPE::IN_LD, ADDR_MODE::AM_A16_R, REG_TYPE::RT_NONE, REG_TYPE::RT_A},
    [0xEE] = {INST_TYPE::IN_XOR, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A},
    [0xEF] = {INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x28},
    [0xF0] = {INST_TYPE::IN_LDH, ADDR_MODE::AM_R_A8, REG_TYPE::RT_A},
    [0xF1] = {INST_TYPE::IN_POP, ADDR_MODE::AM_R, REG_TYPE::RT_AF},
    [0xF2] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_MR, REG_TYPE::RT_A, REG_TYPE::RT_C},
    [0xF3] = {INST_TYPE::IN_DI},
    [0xF5] = {INST_TYPE::IN_PUSH, ADDR_MODE::AM_R, REG_TYPE::RT_AF},
    [0xF6] = {INST_TYPE::IN_OR, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A},
    [0xF7] = {INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x30},
    [0xF8] = {INST_TYPE::IN_LD, ADDR_MODE::AM_HL_SPR, REG_TYPE::RT_HL, REG_TYPE::RT_SP},
    [0xF9] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_R, REG_TYPE::RT_SP, REG_TYPE::RT_HL},
    [0xFA] = {INST_TYPE::IN_LD, ADDR_MODE::AM_R_A16, REG_TYPE::RT_A},
    [0xFB] = {INST_TYPE::IN_EI},
    [0xFE] = {INST_TYPE::IN_CP, ADDR_MODE::AM_R_D8, REG_TYPE::RT_A},
    [0xFF] = {INST_TYPE::IN_RST, ADDR_MODE::AM_IMP, REG_TYPE::RT_NONE, REG_TYPE::RT_NONE, COND_TYPE::CT_NONE, 0x38},
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