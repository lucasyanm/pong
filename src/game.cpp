#include "../include/game.h"

float playerPosY = 0.f;
float playerPosX = 0.f;
UINT color = 0xff0000;

GLOBALVAR const float playerSpeed = 300.f; //units (pixels) per second

// BUG: Not getting when button is released
void simulateGame(
    const Input& input, 
    const float& deltaTimeInSeconds,
    RenderState& renderState
) {
    clearScreen(renderState, 0x00ff00);

    if (isHold(Button::DOWN)) {
        playerPosY -= playerSpeed*deltaTimeInSeconds;
        color = 0xff0000;
    };
    if(isReleased(Button::DOWN)) {
        color = 0x0000ff;
    }

    if (isHold(Button::UP)) {
        playerPosY += playerSpeed*deltaTimeInSeconds;
        color = 0xff0000;
    };
    if(isReleased(Button::UP)) {
        color = 0x0000ff;
    }

    if(isHold(Button::LEFT)) {
        playerPosX -= playerSpeed*deltaTimeInSeconds;
        color = 0xff0000;
    };
    if(isReleased(Button::LEFT)) {
        color = 0x0000ff;
    }    

    if(isHold(Button::RIGHT)) {
        playerPosX += playerSpeed*deltaTimeInSeconds;
        color = 0xff0000;
    };
    if(isReleased(Button::RIGHT)) {
        color = 0x0000ff;
    }

    renderRect(renderState, playerPosX, playerPosY, 10, 10, color);
}