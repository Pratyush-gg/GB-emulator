#include "../../include/cpu.hpp"
#include "../../include/instructions.hpp"
#include "../../include/mmu.hpp"

#include <iostream>

// TODO

bool CPU::check_condition(const Instruction& instruction) {
    if (!instruction.condition.has_value()) {
        return true;
    }

    switch (instruction.condition.value()) {
        case COND_TYPE::CT_NONE:
            return true;
        case COND_TYPE::CT_Z:
            return regs.flags.z();
        case COND_TYPE::CT_NZ:
            return !regs.flags.z();
        case COND_TYPE::CT_C:
            return regs.flags.c();
        case COND_TYPE::CT_NC:
            return !regs.flags.c();
        default:
            std::cerr << "Error: Unknown condition type" << std::endl;
            return false;
    }
}

void CPU::stack_push(uint8_t value) {
    regs.SP--;
    bus->write_data(regs.SP, value);
}

void CPU::stack_push16(uint16_t value) {
    regs.SP -= 2;
    bus->write_data16(regs.SP, value);
}

uint8_t CPU::stack_pop() {
    uint8_t value = bus->read_data(regs.SP);
    regs.SP++;
    return value;
}

uint16_t CPU::stack_pop16() {
    uint16_t value = bus->read_data16(regs.SP);
    regs.SP += 2;
    return value;
}

int CPU::process_NOP() {
    return 0;
}

int CPU::process_STOP() {
    std::cout << "STOP instruction encountered. CPU halted." << std::endl;
    this->halted = true;
    exit(0);
}

int CPU::process_DI() {
    this->interrupt_master_enable = false;
    return 0;
}

int CPU::process_JP() {
    if (check_condition(current_instruction)) {
        regs.PC = fetch_data;
        return 4;
    }
    return 0;
}

int CPU::process_JR() {
    if (check_condition(current_instruction)) {
        regs.PC += static_cast<int8_t>(fetch_data & 0xFF);
        return 4;
    }
    return 0;
}

int CPU::process_CALL() {
    if (check_condition(current_instruction)) {
        stack_push16(regs.PC);
        regs.PC = fetch_data;
        return 12;
    }
    return 0;
}

int CPU::process_RST() {
    if (check_condition(current_instruction)) {
        stack_push16(regs.PC);
        regs.PC = current_instruction.param.value();
        return 12;
    }
    return 0;
}

int CPU::process_RET() {
    int cycles = 0;
    if (current_instruction.condition != COND_TYPE::CT_NONE)
    {
        cycles+= 4;
    }
    if (check_condition(current_instruction)) {
        uint16_t return_address = stack_pop16();
        cycles += 8;
        regs.PC = return_address;
        cycles += 4;
    }
    return cycles;
}

int CPU::process_RETI() {
    this->interrupt_master_enable = true;
    int cycles = process_RET();
    return cycles;
}

int CPU::process_AND() {
    regs.set_register(REG_TYPE::RT_A, regs.read_register(REG_TYPE::RT_A) & fetch_data);
    regs.flags.set_z(regs.read_register(REG_TYPE::RT_A) == 0);
    regs.flags.set_h(true);
    regs.flags.set_c(false);
    regs.flags.set_n(false);
    return 0;
}


int CPU::process_XOR() {
    uint8_t value = fetch_data & 0xFF;
    regs._a ^= value;
    regs.flags.set_z(regs._a == 0);
    regs.flags.set_h(false);
    regs.flags.set_c(false);
    regs.flags.set_n(false);
    return 0;
}

int CPU::process_OR() {
    uint8_t value = fetch_data & 0xFF;
    regs._a |= value;
    regs.flags.set_z(regs._a == 0);
    regs.flags.set_h(false);
    regs.flags.set_c(false);
    regs.flags.set_n(false);
    return 0;
}

int CPU::process_CP() {
    int n = (int)regs._a - (int)fetch_data;
    regs.flags.set_z(n == 0);
    regs.flags.set_h((regs._a & 0xF) < (fetch_data & 0xF));
    regs.flags.set_c(n < 0);
    regs.flags.set_n(true);
    return 0;
}

int CPU::process_LD() {
    if (dest_is_mem) {
        if (current_instruction.reg2 >= REG_TYPE::RT_AF)
        {
            bus->write_data16(mem_dest, fetch_data);
        }
        else {
            bus->write_data(mem_dest, fetch_data);
        }
        return 4;
    }

    if (current_instruction.mode == ADDR_MODE::AM_HL_SPR) {
        regs.flags.set_h((regs.read_register(current_instruction.reg2.value()) & 0x0F) + (fetch_data & 0x0F) > 0x10);
        regs.flags.set_c((regs.read_register(current_instruction.reg2.value()) & 0xFF) + (fetch_data & 0xFF) >= 0x100);

        regs.set_register(current_instruction.reg1.value(), regs.read_register(current_instruction.reg2.value()) + (char)fetch_data);
        return 0;
    }

    regs.set_register(current_instruction.reg1.value(), fetch_data);
}

int CPU::process_LDH() {
    if (current_instruction.reg1 == REG_TYPE::RT_A) {
        regs.set_register(current_instruction.reg1.value(), bus->read_data(0xFF00 | fetch_data));
    }
    else {
        bus->write_data(0xFF00 | fetch_data, regs.read_register(REG_TYPE::RT_A));
    }
    return 4;
}

int CPU::process_PUSH() {
    uint16_t high = (regs.read_register(current_instruction.reg1.value()) >> 8) & 0xFF;
    uint16_t low = regs.read_register(current_instruction.reg1.value()) & 0xFF;
    stack_push(high);
    stack_push(low);
    return 12;
}

int CPU::process_POP() {
    uint16_t low = stack_pop();
    uint16_t high = stack_pop();
    regs.set_register(current_instruction.reg1.value(), (high << 8) | low);

    if (current_instruction.reg1 == REG_TYPE::RT_AF) {
        regs.set_register(current_instruction.reg1.value(), ((high << 8) | low) & 0xFFF0);
    }
    return 12;
}

int CPU::process_INC() {
    uint16_t value = regs.read_register(current_instruction.reg1.value()) + 1;
    int cycles = 0;

    if (current_instruction.reg1 >= REG_TYPE::RT_AF) {
        cycles += 4;
    }
    if (current_instruction.reg1 == REG_TYPE::RT_HL && current_instruction.mode == ADDR_MODE::AM_MR) {
        value = bus->read_data(regs.read_register(REG_TYPE::RT_HL)) + 1;
        bus->write_data(regs.read_register(REG_TYPE::RT_HL), value & 0xFF);
    }
    else {
        regs.set_register(current_instruction.reg1.value(), value);
        value = regs.read_register(current_instruction.reg1.value());
    }
    if ((current_opcode & 0x03) == 0x03) {
        return cycles;
    }

    regs.flags.set_z(false);
    regs.flags.set_n(false);
    regs.flags.set_h((value & 0x0F) == 0);

    return cycles;
}

int CPU::process_DEC() {
    uint16_t value = regs.read_register(current_instruction.reg1.value()) - 1;
    int cycles = 0;

    if (current_instruction.reg1 >= REG_TYPE::RT_AF) {
        cycles += 4;
    }
    if (current_instruction.reg1 == REG_TYPE::RT_HL && current_instruction.mode == ADDR_MODE::AM_MR) {
        value = bus->read_data(regs.read_register(REG_TYPE::RT_HL)) - 1;
        bus->write_data(regs.read_register(REG_TYPE::RT_HL), value);
    }
    else {
        regs.set_register(current_instruction.reg1.value(), value);
        value = regs.read_register(current_instruction.reg1.value());
    }
    if ((current_opcode & 0x0B) == 0x0B) {
        return cycles;
    }

    regs.flags.set_z(false);
    regs.flags.set_n(true);
    regs.flags.set_h((value & 0x0F) == 0x0F);

    return cycles;
}

int CPU::process_ADD() {
    int cycles = 0;
    uint32_t values = regs.read_register(current_instruction.reg1.value()) + fetch_data;

    if (current_instruction.reg1 >= REG_TYPE::RT_AF) {
        cycles += 4;
    }
    if (current_instruction.reg1 == REG_TYPE::RT_SP) {
        values = regs.read_register(current_instruction.reg1.value()) + static_cast<int8_t>(fetch_data);
    }

    bool flag1 = false;
    bool z_flag = (values & 0xFF) == 0;
    bool h_flag = ((regs.read_register(current_instruction.reg1.value()) & 0xF) + (fetch_data & 0xF)) >= 0x10;
    bool c_flag = ((regs.read_register(current_instruction.reg1.value()) & 0xFF) + (fetch_data & 0xFF)) >= 0x100;

    if (current_instruction.reg1 >= REG_TYPE::RT_AF) {
        flag1 = true;
        h_flag = ((regs.read_register(current_instruction.reg1.value()) & 0xFFF) + (fetch_data & 0xFFF)) >= 0x1000;
        c_flag = (uint32_t(regs.read_register(current_instruction.reg1.value())) + uint32_t(fetch_data)) >= 0x10000;
    }
    if (current_instruction.reg1 == REG_TYPE::RT_SP) {
        z_flag = false;
        h_flag = ((regs.read_register(current_instruction.reg1.value()) & 0xF) + (fetch_data & 0xF)) >= 0x10;
        c_flag = ((regs.read_register(current_instruction.reg1.value()) & 0xFF) + (fetch_data & 0xFF)) >= 0x100;
    }

    regs.set_register(current_instruction.reg1.value(), values & 0xFFFF);
    if (!flag1) {
        regs.flags.set_z(z_flag);
    }
    regs.flags.set_h(h_flag);
    regs.flags.set_c(c_flag);
    regs.flags.set_n(false);

    return cycles;
}

int CPU::process_SUB() {
    uint16_t values = regs.read_register(current_instruction.reg1.value()) - fetch_data;
    regs.set_register(current_instruction.reg1.value(), regs.read_register(current_instruction.reg1.value()) - values);

    regs.flags.set_z(values == 0);
    regs.flags.set_h((regs.read_register(current_instruction.reg1.value()) & 0xF) < (fetch_data & 0xF));
    regs.flags.set_c(regs.read_register(current_instruction.reg1.value()) < fetch_data);
    regs.flags.set_n(true);

    return 0;
}

int CPU::process_ADC() {
    uint16_t a = fetch_data;
    uint16_t b = regs.read_register(REG_TYPE::RT_A);
    uint16_t c = regs.flags.c() ? 1 : 0;

    regs.set_register(REG_TYPE::RT_A, (a + b + c) & 0xFF);
    regs.flags.set_z(regs.read_register(REG_TYPE::RT_A) == 0);
    regs.flags.set_h(((a & 0xF) + (b & 0xF) + c) > 0xF);
    regs.flags.set_c((a + b + c) > 0xFF);
    regs.flags.set_n(false);

    return 0;
}

int CPU::process_SBC() {
    uint8_t values = fetch_data + (regs.flags.c() ? 1 : 0);

    int z_flag = (regs.read_register(current_instruction.reg1.value()) - values) == 0;
    int h_flag = ((regs.read_register(current_instruction.reg1.value()) & 0xF)  - (fetch_data & 0xF) - (regs.flags.c() ? 1 : 0)) < 0;
    int c_flag = (regs.read_register(current_instruction.reg1.value()) < values);

    regs.set_register(current_instruction.reg1.value(), regs.read_register(current_instruction.reg1.value()) - values);
    regs.flags.set_z(z_flag);
    regs.flags.set_h(h_flag);
    regs.flags.set_c(c_flag);
    regs.flags.set_n(true);

    return 0;
}

int CPU::process_RLCA() {
    uint8_t values = regs.read_register(REG_TYPE::RT_A);
    bool carry = (values >> 7) & 1;
    values = (values << 1) | carry;
    regs.set_register(REG_TYPE::RT_A, values);

    regs.flags.set_z(false);
    regs.flags.set_n(false);
    regs.flags.set_h(false);
    regs.flags.set_c(carry);
    return 0;
}

int CPU::process_RRCA() {
    uint8_t values = regs.read_register(REG_TYPE::RT_A) & 1;
    regs.set_register(REG_TYPE::RT_A, (regs.read_register(REG_TYPE::RT_A) >> 1) | (values << 7));

    regs.flags.set_z(false);
    regs.flags.set_n(false);
    regs.flags.set_h(false);
    regs.flags.set_c(values);
    return 0;
}

int CPU::process_RLA() {
    uint8_t values = regs.read_register(REG_TYPE::RT_A);
    bool carry = regs.flags.c();
    regs.set_register(REG_TYPE::RT_A, (values << 1) | carry);

    regs.flags.set_z(false);
    regs.flags.set_n(false);
    regs.flags.set_h(false);
    regs.flags.set_c((values >> 7) & 1);
    return 0;
}

int CPU::process_RRA() {
    uint8_t values = regs.read_register(REG_TYPE::RT_A) & 1;
    regs.set_register(REG_TYPE::RT_A, (regs.read_register(REG_TYPE::RT_A) >> 1) | (values << 7));

    regs.flags.set_z(false);
    regs.flags.set_n(false);
    regs.flags.set_h(false);
    regs.flags.set_c(values);
    return 0;
}

int CPU::process_DAA() {
    uint8_t a = 0;
    int carry = 0;

    if (regs.flags.h() || (regs.read_register(REG_TYPE::RT_A) & 0xF) > 9) {
        a = 6;
    }
    if (regs.flags.c() || (!regs.flags.n() && regs.read_register(REG_TYPE::RT_A) > 0x99)) {
        a |= 0x60;
        carry = 1;
    }

    regs.set_register(REG_TYPE::RT_A, regs.read_register(REG_TYPE::RT_A) + (regs.flags.n() ? -a : a));
    regs.flags.set_z(regs.read_register(REG_TYPE::RT_A) == 0);
    regs.flags.set_h(false);
    regs.flags.set_c(carry);
    return 0;
}

int CPU::process_CPL() {
    regs.set_register(REG_TYPE::RT_A, ~regs.read_register(REG_TYPE::RT_A));

    regs.flags.set_n(true);
    regs.flags.set_h(true);
    return 0;
}

int CPU::process_SCF() {
    regs.flags.set_c(true);
    regs.flags.set_n(false);
    regs.flags.set_h(false);
    return 0;
}

int CPU::process_CCF() {
    bool carry = regs.flags.c() ^ 1;
    regs.flags.set_c(carry);
    regs.flags.set_n(false);
    regs.flags.set_h(false);
    return 0;
}

int CPU::process_HALT() {
    std::cout << "HALT instruction encountered. CPU halted." << std::endl;
    this->halted = true;
    return 0;
}

int CPU::process_CB() {
    int cycles = 0;
    uint8_t op = fetch_data;
    register REG_TYPE reg;
    switch (op & 0b111) {
        case 0b000: reg = REG_TYPE::RT_B; break;
        case 0b001: reg = REG_TYPE::RT_C; break;
        case 0b010: reg = REG_TYPE::RT_D; break;
        case 0b011: reg = REG_TYPE::RT_E; break;
        case 0b100: reg = REG_TYPE::RT_H; break;
        case 0b101: reg = REG_TYPE::RT_L; break;
        case 0b110: reg = REG_TYPE::RT_HL; break;
        case 0b111: reg = REG_TYPE::RT_A; break;
        default:
            std::cerr << "Error: Unknown Register for CB instruction: " << static_cast<int>(op) << std::endl;
    }
    uint8_t bit = (op >> 3) & 0b111;
    uint8_t bit_op = (op >> 6) & 0b11;

    // SUPER SUS

    uint8_t reg_value = bus->read_data((regs.read_register(reg)));

    // SUPER SUS
    std::cout << "Processing CB instruction: " << static_cast<int>(op) << " Bit: " << static_cast<int>(bit) << " Bit Op: " << static_cast<int>(bit_op) << " Reg Value: " << static_cast<int>(reg_value) << std::endl;
    cycles += 4;

    if (reg == REG_TYPE::RT_HL) {
        cycles += 8;
    }

    switch (static_cast<int>(bit_op)) {
        case 1: {
            regs.flags.set_z(!(reg_value & (1 << bit)));
            regs.flags.set_n(false);
            regs.flags.set_h(true);
            return cycles;
        }
        case 2: {
            regs.set_register(reg, reg_value & ~(1 << bit));
            return cycles;
        }
        case 3: {
            regs.set_register(reg, reg_value | (1 << bit));
            return cycles;
        }
    }

    switch (static_cast<int>(bit)) {
        case 0: {
            bool setC = false;
            uint8_t result = (reg_value << 1) & 0xFF;

            if ((reg_value & (1 << 7)) != 0) {
                result |= 1;
                setC = true;
            }

            regs.set_register(reg, result);
            regs.flags.set_z(result == 0);
            regs.flags.set_n(false);
            regs.flags.set_h(false);
            regs.flags.set_c(setC);
            return cycles;
        }
        case 1: {
            uint8_t old = reg_value;
            reg_value >>= 1;
            reg_value |= old << 7;

            regs.set_register(reg, reg_value);
            regs.flags.set_z(!reg_value);
            regs.flags.set_n(false);
            regs.flags.set_h(false);
            regs.flags.set_c(old & 1);
            return cycles;
        }
        case 2: {
            uint8_t old = reg_value;
            reg_value = (reg_value << 1);
            reg_value |= regs.flags.c() ? 1 : 0;

            regs.set_register(reg, reg_value);
            regs.flags.set_z(!reg_value);
            regs.flags.set_n(false);
            regs.flags.set_h(false);
            regs.flags.set_c(old & 0x80);
            return cycles;
        }
        case 3: {
            uint8_t old = reg_value;
            reg_value >>= 1;
            reg_value |= (regs.flags.c() ? 1 : 0) << 7;

            regs.set_register(reg, reg_value);
            regs.flags.set_z(!reg_value);
            regs.flags.set_n(false);
            regs.flags.set_h(false);
            regs.flags.set_c(old & 1);
            return cycles;
        }
        case 4: {
            uint8_t old = reg_value;
            reg_value <<= 1;

            regs.set_register(reg, reg_value);
            regs.flags.set_z(!reg_value);
            regs.flags.set_n(false);
            regs.flags.set_h(false);
            regs.flags.set_c(old & 0x80);
            return cycles;
        }
        case 5: {
            regs.set_register(reg, reg_value >> 1);
            regs.flags.set_z(!reg_value);
            regs.flags.set_n(false);
            regs.flags.set_h(false);
            regs.flags.set_c(reg_value & 1);
            return cycles;
        }
        case 6: {
            reg_value = ((reg_value & 0xF0) >> 4) | ((reg_value & 0xF) << 4);
            regs.set_register(reg, reg_value);
            regs.flags.set_z(reg_value == 0);
            regs.flags.set_n(false);
            regs.flags.set_h(false);
            regs.flags.set_c(false);
            return cycles;
        }
        case 7: {
            uint8_t a = reg_value >> 1;
            regs.set_register(reg, a);
            regs.flags.set_z(!a);
            regs.flags.set_n(false);
            regs.flags.set_h(false);
            regs.flags.set_c(reg_value & 1);
            return cycles;
        }
        default:
            std::cerr << "Error: Unknown CB instruction: " << static_cast<int>(op) << std::endl;
            return 0;
    }
    std::cerr << "Error: Unknown CB instruction: " << static_cast<int>(op) << std::endl;
}