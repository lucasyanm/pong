#ifndef RENDERER_H
#define RENDERER_H

#include <windef.h>
#include <minwindef.h>
#include <wingdi.h>

#include <tuple>

struct RenderState {
    LPVOID memory; //LPVOID same as void*
    int width;
    int height;

    BITMAPINFO bitMapInfo;
};

class Renderer {
public:
    //Memory
    static void allocMemroy();
    static void deallocMemory();
    static bool isMemoryAllocated();
    static LPVOID getMemoryAddress();

    //Screen
    static std::tuple<int, int> setSize(int width, int height);
    static int getWidth();
    static int getHeight();
    static void clearScreen(UINT32 color);

    static void renderRect(
        int middleCoordX, 
        int middleCoordY, 
        int width, 
        int height, 
        UINT32 color
    );

    static void render(HDC deviceContext);

    //BitMap
    static void setBitMapInfo(BITMAPINFO bitMapInfo);
    static void setBitMapInfo(
        DWORD size,
        WORD planes,
        WORD bitCount,
        DWORD compression
    );
    static BITMAPINFO getBitMapInfo();

private:
    static RenderState renderState;
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