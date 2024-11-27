#ifndef INPUT_H
#define INPUT_H

//TODO: Change name to KeyboardButton
struct Button {
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
    Button buttons[Button::BUTTONS_COUNT];
};

void resetInput(Input& input);

#endif