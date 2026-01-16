#include "../include/joypad.hpp"

bool JoyPad::joypad_button_select() {
    return button_select;
}

bool JoyPad::joypad_direction_select() {
    return direction_select;
}

void JoyPad::joypad_set_select(uint8_t value) {
    button_select = value & 0x20;
    direction_select = value & 0x10;
}

JoyPad::joypad_state* JoyPad::joypad_get_state() {
    return &controller;
}

uint8_t JoyPad::joypad_get_output() {
    uint8_t output = 0xCF;

    if (!joypad_button_select()) {
        if (joypad_get_state()->start) {
            output &= ~(1 << 3);
        }
        else if (joypad_get_state()->select) {
            output &= ~(1 << 2);
        }
        else if (joypad_get_state()->a) {
            output &= ~(1 << 0);
        }
        else if (joypad_get_state()->b) {
            output &= ~(1 << 1);
        }
    }

    if (!joypad_direction_select()) {
        if (joypad_get_state()->left) {
            output &= ~(1 << 1);
        }
        else if (joypad_get_state()->right) {
            output &= ~(1 << 0);
        }
        else if (joypad_get_state()->up) {
            output &= ~(1 << 2);
        }
        else if (joypad_get_state()->down) {
            output &= ~(1 << 3);
        }
    }
    return output;
}
