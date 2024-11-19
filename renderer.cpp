#include <wingdi.h>
#include <minwindef.h>
#include <algorithm>
#include "utils.cpp"

struct RenderState {
    LPVOID memory; //LPVOID same as void*
    int width;
    int height;

    BITMAPINFO bitMapInfo;
};
GLOBALVAR RenderState renderState;
GLOBALVAR float scale = 0.001f;

INTERNAL void clearScreen(UINT32 color) {
    UINT32* pixel = (UINT32*)renderState.memory;

    for(int i = 0; i < renderState.height; i++) {
        for(int j = 0; j < renderState.width; j++) {
            *pixel++ = color;
        }
    }
}

INTERNAL void renderRectInPixels(int x0, int y0, int x1, int y1, UINT32 color) {
    // TODO: Validation to avoid memory overflow when resizing
    x0 = std::clamp(x0, 0, renderState.width);
    y0 = std::clamp(y0, 0, renderState.height);
    x1 = std::clamp(x1, 0, renderState.width);
    y1 = std::clamp(y1, 0, renderState.height);

    for(int y = y0; y < y1; y++) {

        UINT32* pixel = (UINT32*)renderState.memory + x0 + y * renderState.width;

        for(int x = x0; x < x1; x++) {
            *pixel++ = color;
        }
    }
}

INTERNAL void renderRect(int middleCoordX, int middleCoordY, int width, int height, UINT32 color) {
    // convert to percentage
    middleCoordX *= scale * renderState.height;
    middleCoordY *= scale * renderState.height;
    width *= scale * renderState.height;
    height *= scale * renderState.height;

    // converting to pixel coord
    int x0 = middleCoordX - width;
    int y0 = middleCoordY - height;
    int x1 = middleCoordX + width;
    int y1 = middleCoordY + height;

    renderRectInPixels(x0, y0, x1, y1, color);
}