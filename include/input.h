#ifndef INPUT_H
#define INPUT_H

struct KeyboardButton {
    bool pressed = false;
    bool changed = false;

    enum
    {
        UP,
        DOWN,
        W,
        S,
        LEFT,
        RIGHT,
        ENTER,

        BUTTONS_COUNT
    };
};

struct Input {
    KeyboardButton buttons[KeyboardButton::BUTTONS_COUNT];
};

void resetInput(Input& input);

#endif