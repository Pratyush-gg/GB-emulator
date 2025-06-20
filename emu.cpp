#include <gb_utils.hpp>
#include <cpu.hpp>
#include <cart.hpp>
#include <emu.hpp>
#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

emu_context ectx;

emu_context* emu_get_context() {
    return &ectx;
}

int emu_run(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << "./main" << " <ROM file>" << endl;
        return 1;
    }

    if (!cart_load(argv[1])) {
        cout << "Failed to load the cartridge." << endl;
        return 1;
    }
    print_cart_info();

    // SDL initialization

    // CPU initialization

    ectx.running = true;
    ectx.paused = false;
    ectx.cycles = 0;

    while
}