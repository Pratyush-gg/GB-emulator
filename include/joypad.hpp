#pragma once
#include <cstdint>

class JoyPad {
public:
    struct joypad_state {
        bool a = false;
        bool b = false;
        bool select = false;
        bool start = false;
        bool right = false;
        bool left = false;
        bool up = false;
        bool down = false;
    };

    bool joypad_button_select();
    bool joypad_direction_select();
    void joypad_set_select(uint8_t value);
    joypad_state* joypad_get_state();
    uint8_t joypad_get_output();

private:
    bool button_select = false;
    bool direction_select = false;
    joypad_state controller;

};
