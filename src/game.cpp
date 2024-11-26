#include "../include/game.h"

Player player1;
Player player2;

const float arenaHalfSizeWidth = 85;
const float arenaHalfSizeHeight = 45;

inline void calculatePlayerPosition(
    Player& player, 
    const float& deltaTimeInSeconds
) {
    player.derivativeDerivativePosition -= player.derivativePosition * 10.f;

    player.position = player.position + player.derivativePosition * deltaTimeInSeconds + player.derivativeDerivativePosition * deltaTimeInSeconds * deltaTimeInSeconds * .5f;
    player.derivativePosition = player.derivativePosition + player.derivativeDerivativePosition * deltaTimeInSeconds;
}

// BUG: Delay to start player movement in 50% keyboard
void simulateGame(
    const Input& input, 
    const float& deltaTimeInSeconds,
    RenderState& renderState
) {
    //background
    clearScreen(renderState, mainColor);
    renderRect(
        renderState, 
        0, 0, 
        arenaHalfSizeWidth, 
        arenaHalfSizeHeight, 
        secColor);

    //movement
    player1.derivativeDerivativePosition = 0.f;
    if (isHold(Button::DOWN))
    {
        player1.derivativeDerivativePosition -= 2000;
    };
    if (isHold(Button::UP)) {
        player1.derivativeDerivativePosition += 2000;
    };

    player2.derivativeDerivativePosition = 0.f;
    if (isHold(Button::S))
    {
        player2.derivativeDerivativePosition -= 2000;
    };
    if (isHold(Button::W)) {
        player2.derivativeDerivativePosition += 2000;
    };

    calculatePlayerPosition(player1, deltaTimeInSeconds);
    calculatePlayerPosition(player2, deltaTimeInSeconds);

    //ball
    renderRect(renderState, 0, 0, 1, 1, mainColor);

    //player Right
    renderRect(
        renderState, 
        -80, 
        player2.position, 
        player2.halfWidth, 
        player2.halfHeight, 
        mainColor);
    //player Left
    renderRect(
        renderState, 
        80, 
        player1.position, 
        player1.halfWidth, 
        player2.halfHeight, 
        mainColor);
}


