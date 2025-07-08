#pragma once
#include <cstdint>

class Emulator {
private:
    bool running;
    bool paused;
    uint64_t cycles;
public:
    Emulator():
        running(false),
        paused(false),
        cycles(0)
    {}

    int emu_run(int argc, char** argv);
};
