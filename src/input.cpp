#include "../include/input.h"

void resetInput(Input& input) {
    for (int i = 0; i < KeyboardButton::ButtonsCount; i++) {
        input.buttons[i].changed = false;
    }
}