#include "../include/game.h"

float playerPos, playerDerivativePos;

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

    //movement
    float playerDerivativeDerivativePos = 0.f;
    if (isHold(Button::DOWN))
    {
        playerDerivativeDerivativePos -= 2000;
    };
    if (isHold(Button::UP)) {
        playerDerivativeDerivativePos += 2000;
    };

    playerDerivativeDerivativePos -= playerDerivativePos * 10.f;

    playerPos = playerPos + playerDerivativePos * deltaTimeInSeconds + playerDerivativeDerivativePos * deltaTimeInSeconds * deltaTimeInSeconds * .5f;
    playerDerivativePos = playerDerivativePos + playerDerivativeDerivativePos * deltaTimeInSeconds;

    //ball
    renderRect(renderState, 0, 0, 1, 1, mainColor);

    //player Right
    renderRect(renderState, 80, 0, 2.5, 12, mainColor);
    //player Left
    renderRect(renderState, -80, playerPos, 2.5, 12, mainColor);
}