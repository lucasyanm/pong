#include "../include/game.h"

Player player1;
Player player2;

// BUG: Delay to start player movement
void simulateGame(
    const Input& input, 
    const float& deltaTimeInSeconds,
    RenderState& renderState
) {
    //background
    clearScreen(renderState, mainColor);
    renderRect(renderState, 0, 0, 85, 45, secColor);

    player1.playerDerivativeDerivativePos = 0.f;
    //movement
    if (isHold(Button::DOWN))
    {
        player1.playerDerivativeDerivativePos -= 2000;
    };
    if (isHold(Button::UP)) {
        player1.playerDerivativeDerivativePos += 2000;
    };

    player1.playerDerivativeDerivativePos -= player1.playerDerivativePos * 10.f;

    player1.playerPos = player1.playerPos + player1.playerDerivativePos *deltaTimeInSeconds + player1.playerDerivativeDerivativePos * deltaTimeInSeconds * deltaTimeInSeconds * .5f;
    player1.playerDerivativePos = player1.playerDerivativePos + player1.playerDerivativeDerivativePos * deltaTimeInSeconds;

    //ball
    renderRect(renderState, 0, 0, 1, 1, mainColor);

    //player Right
    renderRect(renderState, 80, 0, 2.5, 12, mainColor);
    //player Left
    renderRect(renderState, -80, player1.playerPos, 2.5, 12, mainColor);
}

