#ifndef GAME_H
#define GAME_H

#include "input.h"
#include "renderer.h"

//Gray
GLOBALVAR const UINT mainColor = 0xebebeb;
//Black
GLOBALVAR const UINT secColor = 0x1c1c1c;
//units (pixels) per second
GLOBALVAR const float playerSpeed = 100.f;

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
struct Score : Object {
    Score(float positionX, float positionY) 
        : Object{
            .positionX = positionX, 
            .positionY = positionY} {};

    int points = 0;

    static constexpr float halfWidth = 1.f;
    static constexpr float halfHeight = 1.f;
};

struct Player : Object, YPhysics {
    Player(
        float positionX,
        float scorePositionX,
        float scorePositionY) 
        : Object{
            .positionX = positionX },
        score(scorePositionX, scorePositionY) {};

    static constexpr float halfWidth = 2.5f;
    static constexpr float halfHeight = 12.f;

    Score score;
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