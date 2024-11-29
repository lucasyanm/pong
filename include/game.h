#ifndef GAME_H
#define GAME_H

#include <string>
#include "input.h"
#include "renderer.h"

//Gray
GLOBALVAR const UINT mainColor = 0xebebeb;
//Black
GLOBALVAR const UINT secColor = 0x1c1c1c;
//Dark Gray
GLOBALVAR const UINT menuNotSelectedColor = 0x2c2c2c;
//units (pixels) per second
GLOBALVAR const float playerSpeed = 100.f;

const float arenaHalfSizeWidth = 85;
const float arenaHalfSizeHeight = 45;

enum GameMode
{
    SINGLEPLAYER,
    LOCAL_MULTIPLAYER
};

enum CurrentScreen
{
    MAIN_MENU,
    GAME
};

#pragma region Primary Objects
struct Object {
    float positionX = 0.f;
    float positionY = 0.f;

    // TODO: Change to var instead of const
    float halfWidth = 1.f;
    float halfHeight = 1.f;
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
};

struct Player : Object, YPhysics {
    Player(
        float positionX,
        float halfWidth,
        float halfHeight,
        float scorePositionX,
        float scorePositionY) 
        : Object{
            .positionX = positionX,
            .halfWidth = halfWidth,
            .halfHeight = halfHeight,},
        score(scorePositionX, scorePositionY) {};

    Score score;
};

struct Ball : Object, XPhysics, YPhysics {
    Ball(
        float derivativePositionX, 
        float derivativeDerivativePositionX) 
        : XPhysics{
            .derivativePositionX = derivativePositionX,
            .derivativeDerivativePositionX = derivativeDerivativePositionX} {};
};

struct MenuButton : Object {
    MenuButton(
        float positionX, 
        float positionY, 
        std::string text = "",
        bool selected = false) 
        : Object{
            .positionX = positionX, 
            .positionY = positionY},
        text(text),
        selected(selected) {};

    static constexpr float halfWidth = .3f;
    static constexpr float halfHeight = .3f;

    bool selected;
    std::string text;
};

#pragma endregion

#pragma region Functions
void simulateGame(
    const Input& input, 
    const float& deltaTimeInSeconds, 
    RenderState& renderState);
#pragma endregion

#endif