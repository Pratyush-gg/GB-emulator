#include "../include/emu.hpp"
#include "../include/instructions.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << "./main" << " <ROM file>" << std::endl;
        // just doing this coz i have a skill issue and couldn't figure out how to pass arguments in VS :kms:
        // remove this before release
		Emulator emulator("../../../roms/Tetris.gb");
		init_instructions();
		emulator.run();
    }
    else {
        Emulator emulator(argv[1]);
        init_instructions();
        emulator.run();
    }

    return 0;
}
