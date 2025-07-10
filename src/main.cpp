#include "../include/cart.hpp"
#include "../include/emu.hpp"
#include "../include/cpu.hpp"

#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << "./main" << " <ROM file>" << std::endl;
        return 1;
    }

    std::shared_ptr<Cartridge> cart = std::make_shared<Cartridge>();
    std::shared_ptr<MMU> mmu = std::make_shared<MMU>();
    std::shared_ptr<CPU> cpu = std::make_shared<CPU>(mmu);

    std::shared_ptr<Emulator> emu = std::make_shared<Emulator>();

    if (!cart->cart_load(argv[1])) {
        std::cout << "Failed to load the cartridge." << std::endl;
        return 1;
    }
    cart->print_cart_info();

    // SDL initialization

    // CPU initialization

    while (emu->running) {
        if (emu->paused) {
            continue;
        }

        if (!cpu->cpu_step()) {
            std::cout << "CPU stopped." << std::endl;
            emu->running = false;
            break;
        }
        emu->cycles += 4;
    }

    return 0;
}
