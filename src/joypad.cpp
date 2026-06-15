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
    uint8_t output = 0xC0; // bits 7-6 are always 1

    if (button_select) {
        output |= 0x20;
    }
    if (direction_select) {
        output |= 0x10;
    }

    // Default bits 3-0 to 1 (released)
    output |= 0x0F;

    if (!button_select) {
        if (joypad_get_state()->start) {
            output &= ~(1 << 3);
        }
        if (joypad_get_state()->select) {
            output &= ~(1 << 2);
        }
        if (joypad_get_state()->b) {
            output &= ~(1 << 1);
        }
        if (joypad_get_state()->a) {
            output &= ~(1 << 0);
        }
    }

    if (!direction_select) {
        if (joypad_get_state()->down) {
            output &= ~(1 << 3);
        }
        if (joypad_get_state()->up) {
            output &= ~(1 << 2);
        }
        if (joypad_get_state()->left) {
            output &= ~(1 << 1);
        }
        if (joypad_get_state()->right) {
            output &= ~(1 << 0);
        }
    }

    return output;
}
