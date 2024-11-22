#include "../include/game.h"

float playerPosY = 0.f;
float playerPosX = 0.f;
UINT color = 0xff0000;

// BUG: Not getting when button is released
void simulateGame(const Input& input, RenderState& renderState) {
    clearScreen(renderState, 0x00ff00);


    if (isPressed(Button::DOWN)) {
        playerPosY -= 1.f;
        color = 0xff0000;
    };
    if(isReleased(Button::DOWN)) {
        color = 0x0000ff;
    }

    if (isPressed(Button::UP)) {
        playerPosY += 1.f;
        color = 0xff0000;
    };
    if(isReleased(Button::UP)) {
        color = 0x0000ff;
    }

    if(isPressed(Button::LEFT)) {
        playerPosX -= 1.f;
        color = 0xff0000;
    };
    if(isReleased(Button::LEFT)) {
        color = 0x0000ff;
    }    

    if(isPressed(Button::RIGHT)) {
        playerPosX += 1.f;
        color = 0xff0000;
    };
    if(isReleased(Button::RIGHT)) {
        color = 0x0000ff;
    }

    renderRect(renderState, playerPosX, playerPosY, 100, 100, color);
}