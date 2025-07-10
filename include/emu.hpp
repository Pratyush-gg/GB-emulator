#pragma once
#include <cstdint>

class Emulator {
public:
    bool running;
    bool paused;
    uint64_t cycles;

    Emulator():
        running(true),
        paused(false),
        cycles(0)
    {}

    int emu_run(int argc, char** argv);
};
