#include "../include/game.h"
#include <algorithm>

#pragma region Global Menu Var
GLOBALVAR MenuButton singlePlayerButton (
    -80.f, 
    -5.f, 
    .3f,
    .3f,
    "SinglePlayer", 
    true);
GLOBALVAR MenuButton localMultiplayerButton {
    10.f, 
    -5.f, 
    .3f,
    .3f,
    "Local Multiplayer"};

GLOBALVAR auto gameMode = GameMode::Singleplayer;
GLOBALVAR auto currentScreen = CurrentScreen::MainMenu;
#pragma endregion

#pragma region Global Game Var
//Player 1
GLOBALVAR Player playerRight { 
    80.f, 
    2.5f,
    12.f,
    10.f, 
    arenaHalfSizeHeight - 10.f };
//Player 2
GLOBALVAR Player playerLeft {
    -80.f,
    2.5f,
    12.f,
    -10.f, 
    arenaHalfSizeHeight - 10.f};

GLOBALVAR Ball ball (
    130.f,
    0.f
);
#pragma endregion


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
        secondaryColor);

    switch (currentScreen)
    {
        case MainMenu: {
            if(isPressed(KeyboardButton::Right)) {
                gameMode = LocalMultiplayer;
            }
            else if(isPressed(KeyboardButton::Left)) {
                gameMode = Singleplayer;
            }
            else if (isPressed(KeyboardButton::Enter))
            {  
                currentScreen = Game;
            }

            renderLetterCharacter(
                renderState,
                "CLASSIC PONG GAME",
                -55.f,
                30.f,
                .5f,
                .5f,
                mainColor);

            renderLetterCharacter(
                renderState, 
                singlePlayerButton.text, 
                singlePlayerButton.positionX,
                singlePlayerButton.positionY, 
                singlePlayerButton.halfWidth, 
                singlePlayerButton.halfHeight, 
                gameMode == GameMode::Singleplayer 
                     ? mainColor
                     : menuNotSelectedColor);   
            
            renderLetterCharacter(
                renderState, 
                localMultiplayerButton.text, 
                localMultiplayerButton.positionX, 
                localMultiplayerButton.positionY, 
                localMultiplayerButton.halfWidth, 
                localMultiplayerButton.halfHeight, 
                gameMode == GameMode::LocalMultiplayer
                     ? mainColor
                     : menuNotSelectedColor);   
        }
            break;
        case Game: {
            #pragma region Movment
            switch (gameMode)
            {
                case Singleplayer:
                    playerRight.derivativeDerivativePositionY = std::max(
                    -1300.f,
                    std::min(
                        1300.f, 
                        (ball.positionY - playerRight.positionY) * 100.f)
                    );
                    break;
                case LocalMultiplayer:
                    playerRight.derivativeDerivativePositionY = 0.f;
                    if (isHold(KeyboardButton::Down))
                    {
                        playerRight.derivativeDerivativePositionY -= 2000;
                    };
                    if (isHold(KeyboardButton::Up)) {
                        playerRight.derivativeDerivativePositionY += 2000;
                    };
                    break;
                default:
                    break;
            }

            playerLeft.derivativeDerivativePositionY = 0.f;
            if (isHold(KeyboardButton::S))
            {
                playerLeft.derivativeDerivativePositionY -= 2000;
            };

            if (isHold(KeyboardButton::W)) {
                playerLeft.derivativeDerivativePositionY += 2000;
            };

            calculatePlayerPosition(playerRight, deltaTimeInSeconds);
            calculatePlayerPosition(playerLeft, deltaTimeInSeconds);
            #pragma endregion

            #pragma region Calculate Ball Pos
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

                //right collision
                if(ball.positionX + ball.halfWidth > arenaHalfSizeWidth) {
                    ball.positionX = 0.f;
                    ball.positionY = 0.f;
                    ball.derivativePositionX *= -1.f;
                    ball.derivativePositionY = 0.f;

                    playerLeft.score.points++;
                }
                //left collision
                else if (ball.positionX - ball.halfWidth < -arenaHalfSizeWidth) {
                    ball.positionX = 0.f;
                    ball.positionY = 0.f;
                    ball.derivativePositionX *= -1.f;
                    ball.derivativePositionY = 0.f;

                    playerRight.score.points++;
                }

                #pragma endregion
            }
            #pragma endregion

            #pragma region Render Objects
            renderNumberCharacter(
                renderState, 
                playerLeft.score.points,
                playerLeft.score.positionX, 
                playerLeft.score.positionY, 
                playerLeft.score.halfWidth * 2, 
                playerLeft.score.halfHeight * 2, 
                mainColor
            );
            renderNumberCharacter(
                renderState, 
                playerRight.score.points,
                playerRight.score.positionX, 
                playerRight.score.positionY, 
                playerRight.score.halfWidth * 2, 
                playerRight.score.halfHeight * 2, 
                mainColor
            );

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
            #pragma endregion
        }
            break;
        default:
            break;
    }


       
}


