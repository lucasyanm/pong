#ifndef GAME_H
#define GAME_H

#include "input.h"
#include "renderer.h"

GLOBALVAR const UINT mainColor = 0xebebeb;
GLOBALVAR const UINT secColor = 0x1c1c1c;

GLOBALVAR const float playerSpeed = 100.f; //units (pixels) per second

#pragma region Primary Objects
struct Object {
    float positionX = 0.f;
    float positionY = 0.f;

    static constexpr float halfWidth = 1.f;
    static constexpr float halfHeight = 1.f;
};
struct YPhysics {
    float derivativePositionY = 0.f; //Velocity
    float derivativeDerivativePositionY = 0.f; //Acceleration
};
struct XPhysics {
    float derivativePositionX = 0.f; // Velocity
    float derivativeDerivativePositionX = 0.f; // Acceleration
};
#pragma endregion

#pragma region Child Objects
struct Player : Object, YPhysics {
    static constexpr float halfWidth = 2.5f;
    static constexpr float halfHeight = 12.f;

    Player(float positionX) 
        : Object{
            .positionX = positionX }{};
};

struct Ball : Object, XPhysics, YPhysics {
    Ball() 
        : XPhysics{
            .derivativePositionX = 100.f,
            .derivativeDerivativePositionX = 0.f} {};
};
#pragma endregion

#pragma region Functions
void simulateGame(
    const Input& input, 
    const float& deltaTimeInSeconds, 
    RenderState& renderState);
#pragma endregion

#endif