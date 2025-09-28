#include "../../include/cpu.hpp"
#include "../../include/instructions.hpp"

#include <iostream>

#include "emu.hpp"

int CPU::fetch_instruction() {
    current_opcode = bus->read_data(regs.PC++);
    current_instruction = instructions[current_opcode];
    if (current_instruction.type == INST_TYPE::IN_NONE) {
        std::cerr << "Error: Unknown instruction" << std::endl;
        return 0;
    }
    return 4;
}

int CPU::execute_instruction(const Instruction& instruction) {
    switch (instruction.type) {
        case INST_TYPE::IN_NOP:  return process_NOP();
        case INST_TYPE::IN_STOP: return process_STOP();
        case INST_TYPE::IN_DI:   return process_DI();
        case INST_TYPE::IN_EI:   return process_EI();
        case INST_TYPE::IN_JP:   return process_JP();
        case INST_TYPE::IN_AND:  return process_AND();
        case INST_TYPE::IN_XOR:  return process_XOR();
        case INST_TYPE::IN_OR:   return process_OR();
        case INST_TYPE::IN_CP:   return process_CP();
        case INST_TYPE::IN_LD:   return process_LD();
        case INST_TYPE::IN_LDH:  return process_LDH();
        case INST_TYPE::IN_PUSH: return process_PUSH();
        case INST_TYPE::IN_POP:  return process_POP();
        case INST_TYPE::IN_JR:   return process_JR();
        case INST_TYPE::IN_CALL: return process_CALL();
        case INST_TYPE::IN_RST:  return process_RST();
        case INST_TYPE::IN_RET:  return process_RET();
        case INST_TYPE::IN_RETI: return process_RETI();
        case INST_TYPE::IN_INC:  return process_INC();
        case INST_TYPE::IN_DEC:  return process_DEC();
        case INST_TYPE::IN_SUB:  return process_SUB();
        case INST_TYPE::IN_ADD:  return process_ADD();
        case INST_TYPE::IN_ADC:  return process_ADC();
        case INST_TYPE::IN_SBC:  return process_SBC();
        case INST_TYPE::IN_RLCA: return process_RLCA();
        case INST_TYPE::IN_RRCA: return process_RRCA();
        case INST_TYPE::IN_RLA:  return process_RLA();
        case INST_TYPE::IN_RRA:  return process_RRA();
        case INST_TYPE::IN_CPL:  return process_CPL();
        case INST_TYPE::IN_DAA:  return process_DAA();
        case INST_TYPE::IN_CCF:  return process_CCF();
        case INST_TYPE::IN_SCF:  return process_SCF();
        case INST_TYPE::IN_HALT: return process_HALT();
        case INST_TYPE::IN_CB:   return process_CB();

        default:
            std::cerr << "Error: Unhandled instruction type: " << static_cast<int>(instruction.type) << std::endl;
            return -1;
    }
}

void CPU::stack_push(const uint8_t value) {
    regs.SP--;
    bus->write_data(regs.SP, value);
}

void CPU::stack_push16(const uint16_t value) {
    regs.SP -= 2;
    bus->write_data16(regs.SP, value);
}

uint8_t CPU::stack_pop() {
    const uint8_t value = bus->read_data(regs.SP);
    regs.SP++;
    return value;
}

uint16_t CPU::stack_pop16() {
    const uint16_t value = bus->read_data16(regs.SP);
    regs.SP += 2;
    return value;
}

void CPU::dbg_update() {
    if (bus->read_data(0xFF02) == 0x81) {
        const unsigned char c = bus->read_data(0xFF01);
        dbg_msg[dbg_msg_size++] = static_cast<char>(c);
        dbg_written = true;
        bus->write_data(0xFF02, 0);
    }
    else dbg_written = false;
}

void CPU::dbg_print() const {
    if (dbg_written) {
        std::cout << "Debug Message: ";
        for (int i = 0; i < dbg_msg_size; ++i) {
            std::cout << dbg_msg[i];
        }
        std::cout << std::endl;
    }
}

void CPU::print_cpu_state(const uint16_t prev_PC) const {
     // std::cout << "PC: " << std::hex << prev_PC << std::dec << " Opcode: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(current_opcode) << std::dec;
     // std::cout << " A: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._a);
     // std::cout << " F: " << (regs.flags.c() ? 'C' : '_') << (regs.flags.h() ? 'H' : '_') << (regs.flags.n() ? 'N' : '_') << (regs.flags.z() ? 'Z' : '_');
     // std::cout << " BC: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._b) << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._c) << std::dec;
     // std::cout << " DE: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._d) << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._e) << std::dec;
     // std::cout << " HL: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._h) << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(regs._l) << std::dec << std::endl;
     // std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bus->read_data(regs.PC)) << " " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bus->read_data(regs.PC + 1)) << std::endl;
}

int CPU::cpu_step() {
    int num_cycles = 0;

    if (this->EI_Triggered) {
        this->interruptHandler->IME = true;
        this->EI_Triggered = false;
    }

    if (!halted) {
        const uint16_t prev_PC = regs.PC;

        dbg_update();
        dbg_print();

        num_cycles += fetch_instruction();
        num_cycles += decode_instruction();

        print_cpu_state(prev_PC);

        if (const int res = execute_instruction(current_instruction); res == -1)
            return 0;
        else num_cycles += res;
    }
    else {
        if (interruptHandler->hasPendingInterrupt()) halted = false;
        num_cycles += 4;
    }

    if (const uint16_t interruptVector = interruptHandler->interruptHandle()) {
        serviceInterrupt(interruptVector);
        return 20;
    }

    return num_cycles;
}

void CPU::serviceInterrupt(const uint16_t interruptVector) {
    stack_push16(regs.PC);
    regs.PC = interruptVector;
}

std::reference_wrapper<RegisterFile> CPU::getRegisterDebug() {
    return regs;
}