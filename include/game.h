#ifndef GAME_H
#define GAME_H

#include "input.h"
#include "renderer.h"

GLOBALVAR const UINT mainColor = 0xebebeb;
GLOBALVAR const UINT secColor = 0x1c1c1c;

GLOBALVAR const float playerSpeed = 100.f; //units (pixels) per second

struct Player {
    float playerPos = 0.f;
    float playerDerivativePos = 0.f;
    float playerDerivativeDerivativePos = 0.f;
};

void simulateGame(
    const Input& input, 
    const float& deltaTimeInSeconds, 
    RenderState& renderState);

#endif