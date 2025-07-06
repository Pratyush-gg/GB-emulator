#include "../include/cart.hpp"
#include "../include/emu.hpp"
#include "../include/cpu.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << "./main" << " <ROM file>" << std::endl;
        return 1;
    }

    Emulator emu;
    Cartridge cart;
    CPU cpu;

    if (!cart.cart_load(argv[1])) {
        std::cout << "Failed to load the cartridge." << std::endl;
        return 1;
    }
    cart.print_cart_info();

    // SDL initialization

    // CPU initialization
}
