#pragma once

#include "gb_utils.hpp"

class emu_context {
    bool running;
    bool paused;
    u64 cycles;
};

int emu_run(int argc, char* argv[]);

emu_context* emu_get_context();