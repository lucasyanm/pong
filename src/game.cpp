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
    player.derivativeDerivativePositionY -= player.derivativePositionY * 10.f;

    player.positionY = player.positionY + player.derivativePositionY * deltaTimeInSeconds + player.derivativeDerivativePositionY * deltaTimeInSeconds * deltaTimeInSeconds * .5f;
    player.derivativePositionY = player.derivativePositionY + player.derivativeDerivativePositionY * deltaTimeInSeconds;

    if(player.positionY + player.halfHeight > arenaHalfSizeHeight) {
        player.positionY = arenaHalfSizeHeight - player.halfHeight;
        player.derivativePositionY = 0.f;
    }
    else if (player.positionY - player.halfHeight < -arenaHalfSizeHeight) {
        player.positionY = -arenaHalfSizeHeight + player.halfHeight;
        player.derivativePositionY = 0.f;
    }
}

inline void calculateBallPosition(
    Ball& ball, 
    const float& deltaTimeInSeconds
) {
    ball.positionY += ball.derivativePositionY * deltaTimeInSeconds;
    ball.positionX += ball.derivativePositionX * deltaTimeInSeconds;

    if( //checking player right collision
        (//checking X axis
        ball.positionX + ball.halfWidth > playerRight.positionX - playerRight.halfWidth
        && ball.positionX - ball.halfWidth < playerRight.positionX + playerRight.halfWidth
        //checking Y axis
        && ball.positionY + ball.halfHeight > playerRight.positionY - playerRight.halfHeight
        && ball.positionY - ball.halfHeight < playerRight.positionY + playerRight.halfHeight)
        || // checking arena collision X axis
        ball.positionX + ball.halfWidth > arenaHalfSizeWidth
        ) {
        ball.positionX = playerRight.positionX - playerRight.halfWidth - ball.halfWidth;
        ball.derivativePositionX *= -1.f;
    } else if ( //checking player left collision
        (//checking X axis
        ball.positionX + ball.halfWidth > playerLeft.positionX - playerLeft.halfWidth
        && ball.positionX - ball.halfWidth < playerLeft.positionX + playerLeft.halfWidth
        //checking Y axis
        && ball.positionY + ball.halfHeight > playerLeft.positionY - playerLeft.halfHeight
        && ball.positionY - ball.halfHeight < playerLeft.positionY + playerLeft.halfHeight)
        || // checking arena collision X axis
        ball.positionX - ball.halfWidth < -arenaHalfSizeWidth
        ) {
        ball.positionX = playerLeft.positionX + playerLeft.halfWidth + ball.halfWidth;
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
    playerRight.derivativeDerivativePositionY = 0.f;
    if (isHold(Button::DOWN))
    {
        playerRight.derivativeDerivativePositionY -= 2000;
    };
    if (isHold(Button::UP)) {
        playerRight.derivativeDerivativePositionY += 2000;
    };

    playerLeft.derivativeDerivativePositionY = 0.f;
    if (isHold(Button::S))
    {
        playerLeft.derivativeDerivativePositionY -= 2000;
    };
    if (isHold(Button::W)) {
        playerLeft.derivativeDerivativePositionY += 2000;
    };

    calculatePlayerPosition(playerRight, deltaTimeInSeconds);
    calculatePlayerPosition(playerLeft, deltaTimeInSeconds);

    //ball
    calculateBallPosition(ball, deltaTimeInSeconds);

    renderRect(
        renderState, 
        ball.positionX, 
        ball.positionY, 
        ball.halfWidth, 
        ball.halfHeight, 
        mainColor);

    //player Left
    renderRect(
        renderState, 
        playerLeft.positionX, 
        playerLeft.positionY, 
        playerLeft.halfWidth, 
        playerLeft.halfHeight, 
        mainColor);

    //player Right
    renderRect(
        renderState, 
        playerRight.positionX, 
        playerRight.positionY, 
        playerRight.halfWidth, 
        playerLeft.halfHeight, 
        mainColor);
}


