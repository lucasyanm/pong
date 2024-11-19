#include <wingdi.h>
#include <minwindef.h>
#include <algorithm>

struct RenderState {
    LPVOID memory; //LPVOID same as void*
    int width;
    int height;

    BITMAPINFO bitMapInfo;
};
RenderState renderState;

void clearScreen(unsigned int color) {
    unsigned int* pixel = (unsigned int*)renderState.memory;

    for(int i = 0; i < renderState.height; i++) {
        for(int j = 0; j < renderState.width; j++) {
            *pixel++ = color;
        }
    }
}

void renderRect(int x0, int y0, int x1, int y1, unsigned int color) {
    // TODO: Validation to avoid memory overflow when resizing
    x0 = std::clamp(x0, 0, renderState.width);
    y0 = std::clamp(y0, 0, renderState.height);
    x1 = std::clamp(x1, 0, renderState.width);
    y1 = std::clamp(y1, 0, renderState.height);

    for(int y = y0; y < y1; y++) {

        unsigned int* pixel = (unsigned int*)renderState.memory + x0 + y * renderState.width;

        for(int x = x0; x < x1; x++) {
            *pixel++ = color;
        }
    }
}