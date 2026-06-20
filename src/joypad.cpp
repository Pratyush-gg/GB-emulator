#include "../include/joypad.hpp"

JoyPad::JoyPad(std::shared_ptr<InterruptHandler> interrupts) : interrupts(interrupts) {}

bool JoyPad::joypad_button_select() {
    return button_select;
}

bool JoyPad::joypad_direction_select() {
    return direction_select;
}

void JoyPad::joypad_set_select(uint8_t value) {
    bool old_button_select = button_select;
    bool old_direction_select = direction_select;

    button_select = value & 0x20;
    direction_select = value & 0x10;

    bool trigger_interrupt = false;
    if (old_button_select && !button_select) {
        if (controller.a || controller.b || controller.select || controller.start) {
            trigger_interrupt = true;
        }
    }
    if (old_direction_select && !direction_select) {
        if (controller.up || controller.down || controller.left || controller.right) {
            trigger_interrupt = true;
        }
    }

    if (trigger_interrupt && interrupts) {
        interrupts->interruptRequest(IT_JOYPAD);
    }
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

void JoyPad::set_button(bool action_button, bool& button_field, bool is_pressed) {
    bool selected = action_button ? !button_select : !direction_select;
    if (!button_field && is_pressed && selected) {
        if (interrupts) {
            interrupts->interruptRequest(IT_JOYPAD);
        }
    }
    button_field = is_pressed;
}

void JoyPad::set_key_state(JoypadKey key, bool is_pressed) {
    switch (key) {
        case JoypadKey::A:      set_button(true, controller.a, is_pressed);      break;
        case JoypadKey::B:      set_button(true, controller.b, is_pressed);      break;
        case JoypadKey::Select: set_button(true, controller.select, is_pressed); break;
        case JoypadKey::Start:  set_button(true, controller.start, is_pressed);  break;
        case JoypadKey::Up:     set_button(false, controller.up, is_pressed);     break;
        case JoypadKey::Down:   set_button(false, controller.down, is_pressed);   break;
        case JoypadKey::Left:   set_button(false, controller.left, is_pressed);   break;
        case JoypadKey::Right:  set_button(false, controller.right, is_pressed);  break;
    }
}
