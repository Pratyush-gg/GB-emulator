#include "../include/emu.hpp"
#include "../include/instructions.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << "./main" << " <ROM file>" << std::endl;
        return 1;
    }

    Emulator emulator(argv[1]);
    init_instructions();
    emulator.run();

    return 0;
}
