#ifndef GAME_H
#define GAME_H

#include "input.h"
#include "renderer.h"

void simulateGame(
    const Input& input, 
    const float& deltaTimeInSeconds, 
    RenderState& renderState);

#endif