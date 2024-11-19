#include <wingdi.h>
#include <minwindef.h>

struct RenderState {
    LPVOID memory; //LPVOID same as void*
    int width;
    int height;

    BITMAPINFO bitMapInfo;
};
RenderState renderState;

void renderBackground() {
    unsigned int* pixel = (unsigned int*)renderState.memory;

    for(int i = 0; i < renderState.height; i++) {
        for(int j = 0; j < renderState.width; j++) {
            *pixel++ = i + j;
        }
    }
}