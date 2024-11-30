#ifndef RENDERER_H
#define RENDERER_H

#include <windef.h>
#include <minwindef.h>
#include <wingdi.h>
#include <string>

#include <tuple>

#include "../include/macros.h"

GLOBALVAR const float RENDER_SCALE = 0.01f;

struct RenderState {
    LPVOID memory; //LPVOID same as void*
    int width;
    int height;

    BITMAPINFO bitMapInfo;
};

#pragma region Memory
void allocMemory(RenderState& renderState);
void deallocMemory(RenderState& renderState);
#pragma endregion

#pragma region BitMap
void setBitMapInfo(
    RenderState& renderState,
    DWORD size,
    WORD planes,
    WORD bitCount,
    DWORD compression
);
#pragma endregion

#pragma region Screen
GLOBALVAR int const letterWidth = 5;

void clearScreen(RenderState& renderState, UINT32 color);

void renderRect(
    RenderState& renderState,
    float middleCoordX, 
    float middleCoordY, 
    float halfWidth, 
    float halfHeight, 
    UINT32 color
);

void renderNumberCharacter(
    RenderState &renderState,
    int number,
    float middleCoordX,
    float middleCoordY,
    float width,
    float height,
    UINT32 color);

void renderLetterCharacter(
    RenderState &renderState,
    std::string text,
    float initialPositionX,
    float initialPositionY,
    float halfWidth,
    float halfHeight,
    UINT32 color);

void render(const RenderState& renderState, HDC deviceContext);
#pragma endregion
#endif