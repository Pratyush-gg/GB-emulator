#pragma once
#include <cstdint>
#include <memory>
#include "interrupt.hpp"

enum class JoypadKey {
    A, B, Select, Start, Up, Down, Left, Right
};

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

    JoyPad(std::shared_ptr<InterruptHandler> interrupts = nullptr);

    bool joypad_button_select();
    bool joypad_direction_select();
    void joypad_set_select(uint8_t value);
    joypad_state* joypad_get_state();
    uint8_t joypad_get_output();
    void set_key_state(JoypadKey key, bool is_pressed);

private:
    bool button_select = false;
    bool direction_select = false;
    joypad_state controller;
    std::shared_ptr<InterruptHandler> interrupts;

    void set_button(bool action_button, bool& button_field, bool is_pressed);
};
