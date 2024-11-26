#include "../include/game.h"

GLOBALVAR Player playerRight {
    .positionX = 80.f
};
GLOBALVAR Player playerLeft {
    .positionX = -80.f
};
GLOBALVAR Ball ball;

const float arenaHalfSizeWidth = 85;
const float arenaHalfSizeHeight = 45;

inline void calculatePlayerPosition(
    Player& player, 
    const float& deltaTimeInSeconds
) {
    player.derivativeDerivativePosition -= player.derivativePosition * 10.f;

    player.position = player.position + player.derivativePosition * deltaTimeInSeconds + player.derivativeDerivativePosition * deltaTimeInSeconds * deltaTimeInSeconds * .5f;
    player.derivativePosition = player.derivativePosition + player.derivativeDerivativePosition * deltaTimeInSeconds;

    if(player.position + player.halfHeight > arenaHalfSizeHeight) {
        player.position = arenaHalfSizeHeight - player.halfHeight;
        player.derivativePosition = 0.f;
    }
    else if (player.position - player.halfHeight < -arenaHalfSizeHeight) {
        player.position = -arenaHalfSizeHeight + player.halfHeight;
        player.derivativePosition = 0.f;
    }
}

inline void calculateBallPosition(
    Ball& ball, 
    const float& deltaTimeInSeconds
) {
    ball.position += ball.derivativePosition * deltaTimeInSeconds;
    ball.positionX += ball.derivativePositionX * deltaTimeInSeconds;

    if( //checking player right collision
        (//checking X axis
        ball.positionX + ball.halfWidth > playerRight.positionX - playerRight.halfWidth
        && ball.positionX - ball.halfWidth < playerRight.positionX + playerRight.halfWidth
        //checking Y axis
        && ball.position + ball.halfHeight > playerRight.position - playerRight.halfHeight
        && ball.position - ball.halfHeight < playerRight.position + playerRight.halfHeight)
        || // checking arena collision X axis
        ball.positionX + ball.halfWidth > arenaHalfSizeWidth
        ) {
        ball.derivativePositionX *= -1.f;
    } 
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
    playerRight.derivativeDerivativePosition = 0.f;
    if (isHold(Button::DOWN))
    {
        playerRight.derivativeDerivativePosition -= 2000;
    };
    if (isHold(Button::UP)) {
        playerRight.derivativeDerivativePosition += 2000;
    };

    playerLeft.derivativeDerivativePosition = 0.f;
    if (isHold(Button::S))
    {
        playerLeft.derivativeDerivativePosition -= 2000;
    };
    if (isHold(Button::W)) {
        playerLeft.derivativeDerivativePosition += 2000;
    };

    calculatePlayerPosition(playerRight, deltaTimeInSeconds);
    calculatePlayerPosition(playerLeft, deltaTimeInSeconds);

    //ball
    calculateBallPosition(ball, deltaTimeInSeconds);

    renderRect(
        renderState, 
        ball.positionX, 
        ball.position, 
        ball.halfWidth, 
        ball.halfHeight, 
        mainColor);

    //player Left
    renderRect(
        renderState, 
        playerLeft.positionX, 
        playerLeft.position, 
        playerLeft.halfWidth, 
        playerLeft.halfHeight, 
        mainColor);

    //player Right
    renderRect(
        renderState, 
        playerRight.positionX, 
        playerRight.position, 
        playerRight.halfWidth, 
        playerLeft.halfHeight, 
        mainColor);
}


