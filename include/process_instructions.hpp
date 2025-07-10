#pragma once

#include "cpu.hpp"

void process_NOP(CPU& cpu);
void process_DI(CPU& cpu);
void process_JP(CPU& cpu);
bool check_condition(CPU& cpu, const Instruction& instruction);
void process_XOR(CPU& cpu);
