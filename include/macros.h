// HACK: Avoid global variables
#define GLOBALVAR static

#define isPressed(b) (input.buttons[b].pressed && input.buttons[b].changed)
#define isReleased(b) (!input.buttons[b].pressed && input.buttons[b].changed)

#define processButton(buttonType, vkCode, pressed)\
    case vkCode:\
        input.buttons[buttonType].pressed = pressed;\
        input.buttons[buttonType].changed = true;\
        break;