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

INTERNAL void clearScreen(UINT32 color) {
    UINT32* pixel = (UINT32*)renderState.memory;

    for(int i = 0; i < renderState.height; i++) {
        for(int j = 0; j < renderState.width; j++) {
            *pixel++ = color;
        }
    }
}

INTERNAL void renderRect(int x0, int y0, int x1, int y1, UINT32 color) {
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