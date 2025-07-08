#include "../include/cpu.hpp"

void CPU::fetch_instruction() {
    current_opcode = bus->read_data(regs.PC);
    regs.PC++;
    switch(current_opcode) {
        case 0x00:
            current_instruction.type = INST_TYPE::IN_NOP;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            break;
        case 0x01:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_D16;
            current_instruction.reg1 = REG_TYPE::RT_BC;
            break;
        case 0x02:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_MR_R;
            current_instruction.reg1 = REG_TYPE::RT_BC;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;
        case 0x03:
            current_instruction.type = INST_TYPE::IN_INC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_BC;
            break;
        case 0x04:
            current_instruction.type = INST_TYPE::IN_INC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_B;
            break;

        case 0x05:
            current_instruction.type = INST_TYPE::IN_DEC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_B;
            break;

        case 0x06:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_B;
            break;

        case 0x07:
            current_instruction.type = INST_TYPE::IN_RLCA;
            break;

        case 0x08:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_A16_R;
            current_instruction.reg2 = REG_TYPE::RT_SP;
            break;

        case 0x09:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_BC;
            break;

        case 0x0A:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_BC;
            break;

        case 0x0B:
            current_instruction.type = INST_TYPE::IN_DEC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_BC;
            break;

        case 0x0C:
            current_instruction.type = INST_TYPE::IN_INC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_C;
            break;

        case 0x0D:
            current_instruction.type = INST_TYPE::IN_DEC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_C;
            break;

        case 0x0E:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_C;
            break;

        case 0x0F:
            current_instruction.type = INST_TYPE::IN_RRCA;
            break;

        case 0x10:
            current_instruction.type = INST_TYPE::IN_STOP;
            break;

        case 0x11:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_D16;
            current_instruction.reg1 = REG_TYPE::RT_DE;
            break;

        case 0x12:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_MR_R;
            current_instruction.reg1 = REG_TYPE::RT_DE;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x13:
            current_instruction.type = INST_TYPE::IN_INC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_DE;
            break;

        case 0x14:
            current_instruction.type = INST_TYPE::IN_INC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_D;
            break;

        case 0x15:
            current_instruction.type = INST_TYPE::IN_DEC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_D;
            break;

        case 0x16:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_D;
            break;

        case 0x17:
            current_instruction.type = INST_TYPE::IN_RLA;
            break;

        case 0x18:
            current_instruction.type = INST_TYPE::IN_JR;
            current_instruction.mode = ADDR_MODE::AM_D8;
            break;

        case 0x19:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_DE;
            break;

        case 0x1A:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_DE;
            break;

        case 0x1B:
            current_instruction.type = INST_TYPE::IN_DEC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_DE;
            break;

        case 0x1C:
            current_instruction.type = INST_TYPE::IN_INC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_E;
            break;

        case 0x1D:
            current_instruction.type = INST_TYPE::IN_DEC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_E;
            break;

        case 0x1E:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_E;
            break;

        case 0x1F:
            current_instruction.type = INST_TYPE::IN_RRA;
            break;

        case 0x20:
            current_instruction.type = INST_TYPE::IN_JR;
            current_instruction.mode = ADDR_MODE::AM_D8;
            current_instruction.condition = COND_TYPE::CT_NZ;
            break;

        case 0x21:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_D16;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            break;

        case 0x22:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_HLI_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x23:
            current_instruction.type = INST_TYPE::IN_INC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            break;

        case 0x24:
            current_instruction.type = INST_TYPE::IN_INC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_H;
            break;

        case 0x25:
            current_instruction.type = INST_TYPE::IN_DEC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_H;
            break;

        case 0x26:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_H;
            break;

        case 0x27:
            current_instruction.type = INST_TYPE::IN_DAA;
            break;

        case 0x28:
            current_instruction.type = INST_TYPE::IN_JR;
            current_instruction.mode = ADDR_MODE::AM_D8;
            current_instruction.condition = COND_TYPE::CT_Z;
            break;

        case 0x29:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x2A:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_HLI;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x2B:
            current_instruction.type = INST_TYPE::IN_DEC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            break;

        case 0x2C:
            current_instruction.type = INST_TYPE::IN_INC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_L;
            break;

        case 0x2D:
            current_instruction.type = INST_TYPE::IN_DEC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_L;
            break;

        case 0x2E:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_L;
            break;

        case 0x2F:
            current_instruction.type = INST_TYPE::IN_CPL;
            break;

        case 0x30:
            current_instruction.type = INST_TYPE::IN_JR;
            current_instruction.mode = ADDR_MODE::AM_D8;
            current_instruction.condition = COND_TYPE::CT_NC;
            break;

        case 0x31:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_D16;
            current_instruction.reg1 = REG_TYPE::RT_SP;
            break;
        case 0x32:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_HLD_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x33:
            current_instruction.type = INST_TYPE::IN_INC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_SP;
            break;

        case 0x34:
            current_instruction.type = INST_TYPE::IN_INC;
            current_instruction.mode = ADDR_MODE::AM_MR;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            break;

        case 0x35:
            current_instruction.type = INST_TYPE::IN_DEC;
            current_instruction.mode = ADDR_MODE::AM_MR;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            break;

        case 0x36:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_MR_D8;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            break;

        case 0x37:
            current_instruction.type = INST_TYPE::IN_SCF;
            break;

        case 0x38:
            current_instruction.type = INST_TYPE::IN_JR;
            current_instruction.mode = ADDR_MODE::AM_D8;
            current_instruction.condition = COND_TYPE::CT_C;
            break;

        case 0x39:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_SP;
            break;

        case 0x3A:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_HLD;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x3B:
            current_instruction.type = INST_TYPE::IN_DEC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_SP;
            break;

        case 0x3C:
            current_instruction.type = INST_TYPE::IN_INC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0x3D:
            current_instruction.type = INST_TYPE::IN_DEC;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0x3E:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0x3F:
            current_instruction.type = INST_TYPE::IN_CCF;
            break;

        case 0x40:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_B;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0x41:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_B;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0x42:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_B;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0x43:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_B;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0x44:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_B;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0x45:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_B;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0x46:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_B;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x47:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_B;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x48:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_C;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0x49:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_C;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0x4A:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_C;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0x4B:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_C;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0x4C:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_C;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0x4D:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_C;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0x4E:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_C;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x4F:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_C;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x50:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_D;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0x51:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_D;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0x52:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_D;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0x53:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_D;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0x54:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_D;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0x55:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_D;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0x56:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_D;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x57:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_D;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x58:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_E;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0x59:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_E;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0x5A:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_E;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0x5B:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_E;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0x5C:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_E;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0x5D:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_E;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0x5E:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_E;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x5F:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_E;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x60:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_H;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0x61:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_H;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0x62:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_H;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0x63:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_H;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;
        case 0x64:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_H;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0x65:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_H;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0x66:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_H;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x67:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_H;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x68:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_L;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0x69:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_L;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0x6A:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_L;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0x6B:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_L;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0x6C:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_L;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0x6D:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_L;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0x6E:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_L;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x6F:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_L;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x70:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_MR_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0x71:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_MR_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0x72:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_MR_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0x73:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_MR_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0x74:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_MR_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0x75:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_MR_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0x76:
            current_instruction.type = INST_TYPE::IN_HALT;
            break;

        case 0x77:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_MR_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x78:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0x79:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0x7A:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0x7B:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0x7C:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0x7D:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0x7E:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x7F:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x80:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0x81:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0x82:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0x83:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0x84:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0x85:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0x86:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x87:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x88:
            current_instruction.type = INST_TYPE::IN_ADC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0x89:
            current_instruction.type = INST_TYPE::IN_ADC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0x8A:
            current_instruction.type = INST_TYPE::IN_ADC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0x8B:
            current_instruction.type = INST_TYPE::IN_ADC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0x8C:
            current_instruction.type = INST_TYPE::IN_ADC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0x8D:
            current_instruction.type = INST_TYPE::IN_ADC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0x8E:
            current_instruction.type = INST_TYPE::IN_ADC;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x8F:
            current_instruction.type = INST_TYPE::IN_ADC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x90:
            current_instruction.type = INST_TYPE::IN_SUB;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_B;
            break;

        case 0x91:
            current_instruction.type = INST_TYPE::IN_SUB;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_C;
            break;

        case 0x92:
            current_instruction.type = INST_TYPE::IN_SUB;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_D;
            break;

        case 0x93:
            current_instruction.type = INST_TYPE::IN_SUB;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_E;
            break;

        case 0x94:
            current_instruction.type = INST_TYPE::IN_SUB;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_H;
            break;

        case 0x95:
            current_instruction.type = INST_TYPE::IN_SUB;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_L;
            break;
        case 0x96:
            current_instruction.type = INST_TYPE::IN_SUB;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x97:
            current_instruction.type = INST_TYPE::IN_SUB;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0x98:
            current_instruction.type = INST_TYPE::IN_SBC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0x99:
            current_instruction.type = INST_TYPE::IN_SBC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0x9A:
            current_instruction.type = INST_TYPE::IN_SBC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0x9B:
            current_instruction.type = INST_TYPE::IN_SBC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0x9C:
            current_instruction.type = INST_TYPE::IN_SBC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0x9D:
            current_instruction.type = INST_TYPE::IN_SBC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0x9E:
            current_instruction.type = INST_TYPE::IN_SBC;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0x9F:
            current_instruction.type = INST_TYPE::IN_SBC;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0xA0:
            current_instruction.type = INST_TYPE::IN_AND;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0xA1:
            current_instruction.type = INST_TYPE::IN_AND;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0xA2:
            current_instruction.type = INST_TYPE::IN_AND;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0xA3:
            current_instruction.type = INST_TYPE::IN_AND;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0xA4:
            current_instruction.type = INST_TYPE::IN_AND;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0xA5:
            current_instruction.type = INST_TYPE::IN_AND;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0xA6:
            current_instruction.type = INST_TYPE::IN_AND;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0xA7:
            current_instruction.type = INST_TYPE::IN_AND;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0xA8:
            current_instruction.type = INST_TYPE::IN_XOR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0xA9:
            current_instruction.type = INST_TYPE::IN_XOR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0xAA:
            current_instruction.type = INST_TYPE::IN_XOR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0xAB:
            current_instruction.type = INST_TYPE::IN_XOR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0xAC:
            current_instruction.type = INST_TYPE::IN_XOR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0xAD:
            current_instruction.type = INST_TYPE::IN_XOR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0xAE:
            current_instruction.type = INST_TYPE::IN_XOR;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0xAF:
            current_instruction.type = INST_TYPE::IN_XOR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0xB0:
            current_instruction.type = INST_TYPE::IN_OR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0xB1:
            current_instruction.type = INST_TYPE::IN_OR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0xB2:
            current_instruction.type = INST_TYPE::IN_OR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0xB3:
            current_instruction.type = INST_TYPE::IN_OR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0xB4:
            current_instruction.type = INST_TYPE::IN_OR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0xB5:
            current_instruction.type = INST_TYPE::IN_OR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0xB6:
            current_instruction.type = INST_TYPE::IN_OR;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0xB7:
            current_instruction.type = INST_TYPE::IN_OR;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0xB8:
            current_instruction.type = INST_TYPE::IN_CP;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_B;
            break;

        case 0xB9:
            current_instruction.type = INST_TYPE::IN_CP;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0xBA:
            current_instruction.type = INST_TYPE::IN_CP;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_D;
            break;

        case 0xBB:
            current_instruction.type = INST_TYPE::IN_CP;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_E;
            break;

        case 0xBC:
            current_instruction.type = INST_TYPE::IN_CP;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_H;
            break;

        case 0xBD:
            current_instruction.type = INST_TYPE::IN_CP;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_L;
            break;

        case 0xBE:
            current_instruction.type = INST_TYPE::IN_CP;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0xBF:
            current_instruction.type = INST_TYPE::IN_CP;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0xC0:
            current_instruction.type = INST_TYPE::IN_RET;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            current_instruction.cond = COND_TYPE::CT_NZ;
            break;

        case 0xC1:
            current_instruction.type = INST_TYPE::IN_POP;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_BC;
            break;

        case 0xC2:
            current_instruction.type = INST_TYPE::IN_JP;
            current_instruction.mode = ADDR_MODE::AM_D16;
            current_instruction.cond = COND_TYPE::CT_NZ;
            break;

        case 0xC3:
            current_instruction.type = INST_TYPE::IN_JP;
            current_instruction.mode = ADDR_MODE::AM_D16;
            break;

        case 0xC4:
            current_instruction.type = INST_TYPE::IN_CALL;
            current_instruction.mode = ADDR_MODE::AM_D16;
            current_instruction.cond = COND_TYPE::CT_NZ;
            break;

        case 0xC5:
            current_instruction.type = INST_TYPE::IN_PUSH;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_BC;
            break;

        case 0xC6:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0xC7:
            current_instruction.type = INST_TYPE::IN_RST;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_NONE;
            current_instruction.param = 0x00;
            break;
        case 0xC8:
            current_instruction.type = INST_TYPE::IN_RET;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_Z;
            break;

        case 0xC9:
            current_instruction.type = INST_TYPE::IN_RET;
            break;

        case 0xCA:
            current_instruction.type = INST_TYPE::IN_JP;
            current_instruction.mode = ADDR_MODE::AM_D16;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_Z;
            break;

        case 0xCB:
            current_instruction.type = INST_TYPE::IN_CB;
            current_instruction.mode = ADDR_MODE::AM_D8;
            break;

        case 0xCC:
            current_instruction.type = INST_TYPE::IN_CALL;
            current_instruction.mode = ADDR_MODE::AM_D16;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_Z;
            break;

        case 0xCD:
            current_instruction.type = INST_TYPE::IN_CALL;
            current_instruction.mode = ADDR_MODE::AM_D16;
            break;

        case 0xCE:
            current_instruction.type = INST_TYPE::IN_ADC;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0xCF:
            current_instruction.type = INST_TYPE::IN_RST;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_NONE;
            current_instruction.param = 0x08;
            break;

        case 0xD0:
            current_instruction.type = INST_TYPE::IN_RET;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_NC;
            break;

        case 0xD1:
            current_instruction.type = INST_TYPE::IN_POP;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_DE;
            break;

        case 0xD2:
            current_instruction.type = INST_TYPE::IN_JP;
            current_instruction.mode = ADDR_MODE::AM_D16;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_NC;
            break;

        case 0xD4:
            current_instruction.type = INST_TYPE::IN_CALL;
            current_instruction.mode = ADDR_MODE::AM_D16;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_NC;
            break;

        case 0xD5:
            current_instruction.type = INST_TYPE::IN_PUSH;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_DE;
            break;

        case 0xD6:
            current_instruction.type = INST_TYPE::IN_SUB;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0xD7:
            current_instruction.type = INST_TYPE::IN_RST;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_NONE;
            current_instruction.param = 0x10;
            break;

        case 0xD8:
            current_instruction.type = INST_TYPE::IN_RET;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_C;
            break;

        case 0xD9:
            current_instruction.type = INST_TYPE::IN_RETI;
            break;

        case 0xDA:
            current_instruction.type = INST_TYPE::IN_JP;
            current_instruction.mode = ADDR_MODE::AM_D16;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_C;
            break;

        case 0xDC:
            current_instruction.type = INST_TYPE::IN_CALL;
            current_instruction.mode = ADDR_MODE::AM_D16;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_C;
            break;

        case 0xDE:
            current_instruction.type = INST_TYPE::IN_SBC;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0xDF:
            current_instruction.type = INST_TYPE::IN_RST;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_NONE;
            current_instruction.param = 0x18;
            break;
        case 0xE0:
            current_instruction.type = INST_TYPE::IN_LDH;
            current_instruction.mode = ADDR_MODE::AM_A8_R;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0xE1:
            current_instruction.type = INST_TYPE::IN_POP;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            break;

        case 0xE2:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_MR_R;
            current_instruction.reg1 = REG_TYPE::RT_C;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0xE5:
            current_instruction.type = INST_TYPE::IN_PUSH;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            break;

        case 0xE6:
            current_instruction.type = INST_TYPE::IN_AND;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0xE7:
            current_instruction.type = INST_TYPE::IN_RST;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_NONE;
            current_instruction.param = 0x20;
            break;

        case 0xE8:
            current_instruction.type = INST_TYPE::IN_ADD;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_SP;
            break;

        case 0xE9:
            current_instruction.type = INST_TYPE::IN_JP;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            break;

        case 0xEA:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_A16_R;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_A;
            break;

        case 0xEE:
            current_instruction.type = INST_TYPE::IN_XOR;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0xEF:
            current_instruction.type = INST_TYPE::IN_RST;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_NONE;
            current_instruction.param = 0x28;
            break;

        case 0xF0:
            current_instruction.type = INST_TYPE::IN_LDH;
            current_instruction.mode = ADDR_MODE::AM_R_A8;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0xF1:
            current_instruction.type = INST_TYPE::IN_POP;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_AF;
            break;

        case 0xF2:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_MR;
            current_instruction.reg1 = REG_TYPE::RT_A;
            current_instruction.reg2 = REG_TYPE::RT_C;
            break;

        case 0xF3:
            current_instruction.type = INST_TYPE::IN_DI;
            break;

        case 0xF5:
            current_instruction.type = INST_TYPE::IN_PUSH;
            current_instruction.mode = ADDR_MODE::AM_R;
            current_instruction.reg1 = REG_TYPE::RT_AF;
            break;

        case 0xF6:
            current_instruction.type = INST_TYPE::IN_OR;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0xF7:
            current_instruction.type = INST_TYPE::IN_RST;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_NONE;
            current_instruction.param = 0x30;
            break;
        case 0xF8:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_HL_SPR;
            current_instruction.reg1 = REG_TYPE::RT_HL;
            current_instruction.reg2 = REG_TYPE::RT_SP;
            break;

        case 0xF9:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_R;
            current_instruction.reg1 = REG_TYPE::RT_SP;
            current_instruction.reg2 = REG_TYPE::RT_HL;
            break;

        case 0xFA:
            current_instruction.type = INST_TYPE::IN_LD;
            current_instruction.mode = ADDR_MODE::AM_R_A16;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0xFB:
            current_instruction.type = INST_TYPE::IN_EI;
            break;

        case 0xFE:
            current_instruction.type = INST_TYPE::IN_CP;
            current_instruction.mode = ADDR_MODE::AM_R_D8;
            current_instruction.reg1 = REG_TYPE::RT_A;
            break;

        case 0xFF:
            current_instruction.type = INST_TYPE::IN_RST;
            current_instruction.mode = ADDR_MODE::AM_IMP;
            current_instruction.reg1 = REG_TYPE::RT_NONE;
            current_instruction.reg2 = REG_TYPE::RT_NONE;
            current_instruction.condition = COND_TYPE::CT_NONE;
            current_instruction.param = 0x38;
            break;

        default:
            current_instruction.type = INST_TYPE::IN_ERR;
            break;
    }
}

void CPU::decode_instruction() {
    Instruction &inst = this->current_instruction;
    switch (inst.type) {
        case INST_TYPE::IN_LD:
            if (inst.mode == ADDR_MODE::AM_R_D16) {
                inst.param = bus->read_data(regs.PC) | (bus->read_data(regs.PC + 1) << 8);
                regs.PC += 2;
            } else if (inst.mode == ADDR_MODE::AM_R_R) {
                // No additional data needed
            } else if (inst.mode == ADDR_MODE::AM_MR_R) {
                inst.param = regs.get_register(inst.reg1.value());
            }
            break;
        // Handle other instruction types...
        default:
            break;
    }
}

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
