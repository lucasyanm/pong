#include "renderer.h"

#include <algorithm>
#include <numeric>
#include <memoryapi.h>

//PUBLIC

//Memory
void Renderer::allocMemroy() {
    Renderer::deallocMemory();

    int bufferSize = renderState.width * renderState.height * sizeof(UINT32);

    renderState.memory = VirtualAlloc(
        NULL, 
        bufferSize, 
        MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE
    );
}

void Renderer::deallocMemory() { 
    if(Renderer::isMemoryAllocated())
        VirtualFree(renderState.memory, 0, MEM_RELEASE);
};

LPVOID Renderer::getMemoryAddress() { return renderState.memory; };

bool Renderer::isMemoryAllocated() { return renderState.memory != NULL; };

//Screen
void Renderer::clearScreen(UINT32 color) {
    UINT32* pixel = (UINT32*)renderState.memory;

    for(int i = 0; i < renderState.height; i++) {
        for(int j = 0; j < renderState.width; j++) {
            *pixel++ = color;
        }
    }
}

void Renderer::renderRect(
    int middleCoordX, 
    int middleCoordY, 
    int width, 
    int height, 
    UINT32 color
) {
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

std::tuple<int, int> Renderer::setSize(int width, int height) {
    renderState.width = width;
    renderState.height = height;

    return std::make_tuple(width, height);
}

int Renderer::getWidth() { return renderState.width; }

int Renderer::getHeight() { return renderState.height; }

void Renderer::render(HDC deviceContext) {
    StretchDIBits(
        deviceContext, 
        0, 0, renderState.width, renderState.height, 
        0, 0, renderState.width, renderState.height, 
        renderState.memory, 
        &renderState.bitMapInfo, 
        DIB_RGB_COLORS, 
        SRCCOPY
    );
}

//BitMap
void Renderer::setBitMapInfo(BITMAPINFO bitMapInfo) { renderState.bitMapInfo = bitMapInfo; }

void Renderer::setBitMapInfo(
    DWORD size,
    WORD planes,
    WORD bitCount,
    DWORD compression
) {
    renderState.bitMapInfo.bmiHeader.biSize = size;
    renderState.bitMapInfo.bmiHeader.biWidth = renderState.width;
    renderState.bitMapInfo.bmiHeader.biHeight = renderState.height;
    renderState.bitMapInfo.bmiHeader.biPlanes = planes;
    renderState.bitMapInfo.bmiHeader.biBitCount = bitCount;
    renderState.bitMapInfo.bmiHeader.biCompression = compression;
};

BITMAPINFO Renderer::getBitMapInfo() { return renderState.bitMapInfo; }

//PRIVATE
RenderState Renderer::renderState;

void Renderer::renderRectInPixels(
    int x0, 
    int y0, 
    int x1, 
    int y1, 
    UINT32 color
) {
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

