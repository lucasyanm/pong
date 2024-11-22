#ifndef INPUT_H
#define INPUT_H

struct Button {
    bool pressed = false;
    bool changed = false;

    enum
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,

        BUTTONS_COUNT
    };
};

struct Input {
    Button buttons[Button::BUTTONS_COUNT];
};

void resetInput(Input& input);

#endif