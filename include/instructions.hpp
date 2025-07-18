#pragma once
#include <cstdint>
#include <optional>

enum class ADDR_MODE {
    AM_IMP,
    AM_R_D16,
    AM_R_R,
    AM_MR_R,
    AM_R,
    AM_R_D8,
    AM_R_MR,
    AM_R_HLI,
    AM_R_HLD,
    AM_HLI_R,
    AM_HLD_R,
    AM_R_A8,
    AM_A8_R,
    AM_HL_SPR,
    AM_D16,
    AM_D8,
    AM_D16_R,
    AM_MR_D8,
    AM_MR,
    AM_A16_R,
    AM_R_A16
};

enum class REG_TYPE {
    RT_NONE,
    RT_A,
    RT_F,
    RT_B,
    RT_C,
    RT_D,
    RT_E,
    RT_H,
    RT_L,
    RT_AF,
    RT_BC,
    RT_DE,
    RT_HL,
    RT_SP,
    RT_PC
};

enum class INST_TYPE {
    IN_NONE,
    IN_NOP,
    IN_LD,
    IN_INC,
    IN_DEC,
    IN_RLCA,
    IN_ADD,
    IN_RRCA,
    IN_STOP,
    IN_RLA,
    IN_JR,
    IN_RRA,
    IN_DAA,
    IN_CPL,
    IN_SCF,
    IN_CCF,
    IN_HALT,
    IN_ADC,
    IN_SUB,
    IN_SBC,
    IN_AND,
    IN_XOR,
    IN_OR,
    IN_CP,
    IN_POP,
    IN_JP,
    IN_PUSH,
    IN_RET,
    IN_CB,
    IN_CALL,
    IN_RETI,
    IN_LDH,
    IN_JPHL,
    IN_DI,
    IN_EI,
    IN_RST,
    IN_ERR,
    IN_RLC,
    IN_RRC,
    IN_RL,
    IN_RR,
    IN_SLA,
    IN_SRA,
    IN_SWAP,
    IN_SRL,
    IN_BIT,
    IN_RES,
    IN_SET
};

enum class COND_TYPE {
    CT_NONE,
    CT_Z,
    CT_NZ,
    CT_C,
    CT_NC,
    CT_PO,
    CT_PE,
    CT_P,
    CT_M
};

struct Instruction {
    INST_TYPE type {INST_TYPE::IN_NONE};
    ADDR_MODE mode {};
    std::optional<REG_TYPE> reg1{};
    std::optional<REG_TYPE> reg2{};
    std::optional<COND_TYPE> condition{};
    std::optional<uint16_t> param{};

    // The main constructor for your table
    constexpr Instruction(
        INST_TYPE t = INST_TYPE::IN_NONE,
        ADDR_MODE m = ADDR_MODE::AM_IMP,
        std::optional<REG_TYPE> r1 = std::nullopt,
        std::optional<REG_TYPE> r2 = std::nullopt,
        std::optional<COND_TYPE> c = std::nullopt,
        std::optional<uint16_t> p = std::nullopt)
        : type(t), mode(m), reg1(r1), reg2(r2), condition(c), param(p) {}
};

extern Instruction instructions[256];
void init_instructions();