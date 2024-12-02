#ifndef INPUT_H
#define INPUT_H

struct KeyboardButton {
    bool pressed = false;
    bool changed = false;

    enum
    {
        Up,
        Down,
        W,
        S,
        Left,
        Right,
        Enter,

        ButtonsCount
    };
};

struct Input {
    KeyboardButton buttons[KeyboardButton::ButtonsCount];
};

void resetInput(Input& input);

#endif