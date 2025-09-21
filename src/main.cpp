#include "../include/emu.hpp"
#include "../include/instructions.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    Emulator emulator(argv[1]);
    init_instructions();
    emulator.run();

    return 0;
}
