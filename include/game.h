#ifndef GAME_H
#define GAME_H

#include "input.h"
#include "renderer.h"

GLOBALVAR const UINT mainColor = 0xebebeb;
GLOBALVAR const UINT secColor = 0x1c1c1c;

GLOBALVAR const float playerSpeed = 100.f; //units (pixels) per second

struct Player {
    float position = 0.f; //Y
    float positionX = 0.f;

    float derivativePosition = 0.f; // Velocity (Y)
    float derivativeDerivativePosition = 0.f; // Acceleration (Y)


    static constexpr float halfWidth = 2.5f;
    static constexpr float halfHeight = 12.f;
};

// TODO : Refact inheritance
struct Ball : Player {
    static constexpr float halfWidth = 1.f;
    static constexpr float halfHeight = 1.f;

    float derivativePositionX = 50.f;
    float derivativeDerivativePositionX = 0.f;
};

void simulateGame(
    const Input& input, 
    const float& deltaTimeInSeconds, 
    RenderState& renderState);

#endif