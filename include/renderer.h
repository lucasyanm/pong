#ifndef RENDERER_H
#define RENDERER_H

#include <windef.h>
#include <minwindef.h>
#include <wingdi.h>

struct RenderState {
    LPVOID memory; //LPVOID same as void*
    int width;
    int height;

    BITMAPINFO bitMapInfo;
};

class Renderer {
public:
    static RenderState renderState;

    static void clearScreen(UINT32 color);

    static void renderRect(
        int middleCoordX, 
        int middleCoordY, 
        int width, 
        int height, 
        UINT32 color
    );

private:
    static constexpr float scale = 0.001f;

    static void renderRectInPixels(
        int x0, 
        int y0, 
        int x1, 
        int y1, 
        UINT32 color
    );
};

#endif