#ifndef RENDERER_H
#define RENDERER_H

#include <windef.h>
#include <minwindef.h>
#include <wingdi.h>

#include <tuple>

#include "../include/macros.h"

// TODO: Rename to renderScale
GLOBALVAR const float scale = 0.01f;

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
void clearScreen(RenderState& renderState, UINT32 color);

void renderRect(
    RenderState& renderState,
    int middleCoordX, 
    int middleCoordY, 
    int halfWidth, 
    int halfHeight, 
    UINT32 color
);

void renderNumberCharacter(
    RenderState &renderState,
    int number,
    int middleCoordX,
    int middleCoordY,
    int width,
    int height,
    UINT32 color);

void render(const RenderState& renderState, HDC deviceContext);
#pragma endregion
#endif