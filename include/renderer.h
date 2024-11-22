#ifndef RENDERER_H
#define RENDERER_H

#include <windef.h>
#include <minwindef.h>
#include <wingdi.h>

#include <tuple>

#include "../include/macros.h"

GLOBALVAR constexpr float scale = 0.001f;

struct RenderState {
    LPVOID memory; //LPVOID same as void*
    int width;
    int height;

    BITMAPINFO bitMapInfo;
};
GLOBALVAR RenderState renderState;

#pragma region Memory
void allocMemory();
void deallocMemory();
bool isMemoryAllocated();
#pragma endregion

#pragma region BitMap
void setBitMapInfo(BITMAPINFO bitMapInfo);
void setBitMapInfo(
    DWORD size,
    WORD planes,
    WORD bitCount,
    DWORD compression
);
#pragma endregion

#pragma region Screen
std::tuple<int, int> setSize(int width, int height);
int getWidth();
int getHeight();
void clearScreen(UINT32 color);

void renderRect(
    int middleCoordX, 
    int middleCoordY, 
    int width, 
    int height, 
    UINT32 color
);
void renderRectInPixels(
    int x0, 
    int y0, 
    int x1, 
    int y1, 
    UINT32 color
);

void render(HDC deviceContext);
#pragma endregion
#endif