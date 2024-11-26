#include "../include/game.h"

Player player1;
Player player2;

inline void calculatePlayerPosition(
    Player& player, 
    const float& deltaTimeInSeconds
) {
    player.playerDerivativeDerivativePos -= player.playerDerivativePos * 10.f;

    player.playerPos = player.playerPos + player.playerDerivativePos * deltaTimeInSeconds + player.playerDerivativeDerivativePos * deltaTimeInSeconds * deltaTimeInSeconds * .5f;
    player.playerDerivativePos = player.playerDerivativePos + player.playerDerivativeDerivativePos * deltaTimeInSeconds;
}

// BUG: Delay to start player movement in 50% keyboard
void simulateGame(
    const Input& input, 
    const float& deltaTimeInSeconds,
    RenderState& renderState
) {
    //background
    clearScreen(renderState, mainColor);
    renderRect(renderState, 0, 0, 85, 45, secColor);

    //movement
    player1.playerDerivativeDerivativePos = 0.f;
    if (isHold(Button::DOWN))
    {
        player1.playerDerivativeDerivativePos -= 2000;
    };
    if (isHold(Button::UP)) {
        player1.playerDerivativeDerivativePos += 2000;
    };

    player2.playerDerivativeDerivativePos = 0.f;
    if (isHold(Button::S))
    {
        player2.playerDerivativeDerivativePos -= 2000;
    };
    if (isHold(Button::W)) {
        player2.playerDerivativeDerivativePos += 2000;
    };

    calculatePlayerPosition(player1, deltaTimeInSeconds);
    calculatePlayerPosition(player2, deltaTimeInSeconds);

    //ball
    renderRect(renderState, 0, 0, 1, 1, mainColor);

    //player Right
    renderRect(renderState, -80, player2.playerPos, 2.5, 12, mainColor);
    //player Left
    renderRect(renderState, 80, player1.playerPos, 2.5, 12, mainColor);
}


