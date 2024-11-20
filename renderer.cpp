#include <wingdi.h>
#include <minwindef.h>
#include <algorithm>
#include "utils.cpp"
#include <numeric>

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
    // calculate aspect ratio
    int greaterCommonDivisor = std::gcd(renderState.width, renderState.height);
    int aspectWidth = renderState.width / greaterCommonDivisor;
    int aspectHeight = renderState.height / greaterCommonDivisor;

    // define multiplier
    int multiplier = aspectHeight > aspectWidth ? renderState.width : renderState.height;
    
    // convert to percentage
    middleCoordX *= scale * multiplier;
    middleCoordY *= scale * multiplier;
    width *= scale * multiplier;
    height *= scale * multiplier;

    middleCoordX += renderState.width / 2;
    middleCoordY += renderState.height / 2;

    // convert to pixel coord
    int x0 = middleCoordX - width;
    int y0 = middleCoordY - height;
    int x1 = middleCoordX + width;
    int y1 = middleCoordY + height;

    renderRectInPixels(x0, y0, x1, y1, color);
}