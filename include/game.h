#ifndef GAME_H
#define GAME_H

#include <string>
#include "input.h"
#include "renderer.h"

//Gray
GLOBALVAR const UINT MAIN_COLOR = 0xebebeb;
//Black
GLOBALVAR const UINT SECONDARY_COLOR = 0x1c1c1c;
//Dark Gray
GLOBALVAR const UINT MENU_NOT_SELECTED_COLOR = 0x2c2c2c;

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
        float letterPixelHalfWidth = 0,
        float letterPixelHalfHeight = 0,
        std::string text = "",
        bool selected = false) 
        : Object{
            .positionX = positionX, 
            .positionY = positionY,
            .halfWidth = letterPixelHalfWidth,
            .halfHeight = letterPixelHalfHeight},
        text(text),
        selected(selected) {};

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