#include "../include/emu.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << "./main" << " <ROM file>" << std::endl;
        return 1;
    }

    Emulator emulator(argv[1]);
    emulator.run();

    return 0;
}
