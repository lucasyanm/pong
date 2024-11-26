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

void calculatePlayerPosition(
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

bool checkBallCollisionWithPlayer(
    Player& player
) {
    return // checking X axis
        ball.positionX + ball.halfWidth > player.positionX - player.halfWidth 
        && ball.positionX - ball.halfWidth < player.positionX + player.halfWidth
        // checking Y axis
        && ball.positionY + ball.halfHeight > player.positionY - player.halfHeight 
        && ball.positionY - ball.halfHeight < player.positionY + player.halfHeight;
}

void calculateBallVelocityBasedOnPlayer(
    Player& player
) {
    ball.derivativePositionX *= -1.f;

    ball.derivativePositionY = 
        (ball.positionY - player.positionY) * 2 //based on ball position relative to player
        + player.derivativePositionY * .75f;
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

    #pragma region Calculate Ball Position
    {
        ball.positionY += ball.derivativePositionY * deltaTimeInSeconds;
        ball.positionX += ball.derivativePositionX * deltaTimeInSeconds;

        #pragma region Player

        //checking player right collision
        if (checkBallCollisionWithPlayer(playerRight)) {
            ball.positionX = playerRight.positionX - playerRight.halfWidth - ball.halfWidth;
            calculateBallVelocityBasedOnPlayer(playerRight);
        } 
        //checking player left collision
        else if (checkBallCollisionWithPlayer(playerLeft)) {
            ball.positionX = playerLeft.positionX + playerLeft.halfWidth + ball.halfWidth;
            calculateBallVelocityBasedOnPlayer(playerLeft);
        }

        #pragma endregion

        #pragma region Arena

        //checking arena axis Y collision
        if (ball.positionY + ball.halfHeight > arenaHalfSizeHeight) {
            ball.positionY = arenaHalfSizeHeight - ball.halfHeight;
            ball.derivativePositionY *= -1.f;
        }
        else if (ball.positionY - ball.halfHeight < -arenaHalfSizeHeight) {
            ball.positionY = -arenaHalfSizeHeight + ball.halfHeight;
            ball.derivativePositionY *= -1.f;
        }

        //checking arena axis X collision
        if(ball.positionX + ball.halfWidth > arenaHalfSizeWidth) {
            ball.positionX = 0.f;
            ball.positionY = 0.f;
            ball.derivativePositionX *= -1.f;
            ball.derivativePositionY = 0.f;
        }
        else if (ball.positionX - ball.halfWidth < -arenaHalfSizeWidth) {
            ball.positionX = 0.f;
            ball.positionY = 0.f;
            ball.derivativePositionX *= -1.f;
            ball.derivativePositionY = 0.f;
        }

        #pragma endregion
    }
    #pragma endregion

    renderRect(
        renderState, 
        ball.positionX, 
        ball.positionY, 
        ball.halfWidth, 
        ball.halfHeight, 
        mainColor);
    renderRect(
        renderState, 
        playerLeft.positionX, 
        playerLeft.positionY, 
        playerLeft.halfWidth, 
        playerLeft.halfHeight, 
        mainColor);
    renderRect(
        renderState, 
        playerRight.positionX, 
        playerRight.positionY, 
        playerRight.halfWidth, 
        playerLeft.halfHeight, 
        mainColor);
}


