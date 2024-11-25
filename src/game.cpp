#include "../include/game.h"

float playerPosY = 0.f;
const UINT mainColor = 0xebebeb;
const UINT secColor = 0x1c1c1c;

GLOBALVAR const float playerSpeed = 100.f; //units (pixels) per second

// BUG: Delay to start player movement
void simulateGame(
    const Input& input, 
    const float& deltaTimeInSeconds,
    RenderState& renderState
) {
    //background
    clearScreen(renderState, mainColor);
    renderRect(renderState, 0, 0, 85, 45, secColor);

    if (isHold(Button::DOWN))
    {
        playerPosY -= playerSpeed*deltaTimeInSeconds;
    };
    if (isHold(Button::UP)) {
        playerPosY += playerSpeed*deltaTimeInSeconds;
    };

    //ball
    renderRect(renderState, 0, 0, 1, 1, mainColor);

    //player Right
    renderRect(renderState, 80, 0, 2.5, 12, mainColor);
    //player Left
    renderRect(renderState, -80, playerPosY, 2.5, 12, mainColor);
}