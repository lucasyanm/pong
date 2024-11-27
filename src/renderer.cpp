#include "renderer.h"

#include <algorithm>
#include <numeric>
#include <memoryapi.h>

#pragma region Memory
void allocMemory(RenderState& renderState) {
    deallocMemory(renderState);

    int bufferSize = renderState.width * renderState.height * sizeof(UINT32);

    renderState.memory = VirtualAlloc(
        NULL, 
        bufferSize, 
        MEM_COMMIT | MEM_RESERVE, 
        PAGE_READWRITE
    );
}

void deallocMemory(RenderState& renderState) { 
    if(renderState.memory != NULL)
        VirtualFree(renderState.memory, 0, MEM_RELEASE);
};
#pragma endregion

#pragma region Screen
void clearScreen(RenderState& renderState, UINT32 color) {
    UINT32* pixel = (UINT32*)renderState.memory;

    for(int i = 0; i < renderState.height; i++) {
        for(int j = 0; j < renderState.width; j++) {
            *pixel++ = color;
        }
    }
}

void renderRectInPixels(
    RenderState& renderState,
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

void renderRect(
    RenderState& renderState,
    int middleCoordX, 
    int middleCoordY, 
    int halfWidth, 
    int halfHeight, 
    UINT32 color
) {
    // calculate aspect ratio
    int greaterCommonDivisor = std::gcd(renderState.width, renderState.height);
    int aspectWidth = greaterCommonDivisor ? renderState.width / greaterCommonDivisor : 0;
    int aspectHeight = greaterCommonDivisor ? renderState.height / greaterCommonDivisor : 0;

    // define multiplier
    int multiplier = aspectHeight > aspectWidth ? renderState.width : renderState.height;
    
    // convert to percentage
    middleCoordX *= scale * multiplier;
    middleCoordY *= scale * multiplier;
    halfWidth *= scale * multiplier;
    halfHeight *= scale * multiplier;

    middleCoordX += renderState.width / 2;
    middleCoordY += renderState.height / 2;

    // convert to pixel coord
    int x0 = middleCoordX - halfWidth;
    int y0 = middleCoordY - halfHeight;
    int x1 = middleCoordX + halfWidth;
    int y1 = middleCoordY + halfHeight;

    renderRectInPixels(renderState, x0, y0, x1, y1, color);
}

void render(const RenderState& renderState, HDC deviceContext) {
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

void renderNumberCharacter(
    RenderState& renderState, 
    int number,
    int middleCoordX, 
    int middleCoordY, 
    int width, 
    int height, 
    UINT32 color
) {
    bool alreadyDraw = false;
    while (!alreadyDraw || number) {
        alreadyDraw = true;

        int digit = number % 10;
        number /= 10;

        switch (digit) {
            case 0: {
                //all left
                renderRect(
                    renderState, 
                    middleCoordX - width,
                    middleCoordY,
                    width / 2,
                    height * 2.5f,
                    color);
                //all right
                renderRect(
                    renderState, 
                    middleCoordX + width,
                    middleCoordY,
                    width / 2,
                    height * 2.5f,
                    color);
                //middle bottom
                renderRect(
                    renderState, 
                    middleCoordX,
                    middleCoordY - height * 2.f,
                    width,
                    height / 2.f,
                    color);
                //middle top
                renderRect(
                    renderState, 
                    middleCoordX,
                    middleCoordY + height * 2.f,
                    width,
                    height / 2.f,
                    color);
            }
                break;
            case 1: {
                //all right
                renderRect(
                    renderState, 
                    middleCoordX + width,
                    middleCoordY,
                    width / 2,
                    height * 2.5f,
                    color);
            }
                break;
            case 2: {
                //all top
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY + height * 2.f,
                    width * 1.5f,
                    height / 2,
                    color);
                //between top right
                renderRect(
                    renderState,
                    middleCoordX + width,
                    middleCoordY + height,
                    width / 2.f,
                    height / 2.f,
                    color);
                //all middle
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY,
                    width * 1.5f,
                    height / 2.f,
                    color);
                //between bottom left
                renderRect(
                    renderState,
                    middleCoordX - width,
                    middleCoordY - height,
                    width / 2.f,
                    height / 2.f,
                    color);
                //all bottom
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY - height * 2.f,
                    width * 1.5f,
                    height / 2.f,
                    color);
            }
                break;
            case 3: {
                //all top
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY + height * 2.f,
                    width * 1.5f,
                    height / 2,
                    color);
                //between top right
                renderRect(
                    renderState,
                    middleCoordX + width,
                    middleCoordY + height,
                    width / 2.f,
                    height / 2.f,
                    color);
                //all middle
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY,
                    width * 1.5f,
                    height / 2.f,
                    color);
                //between bottom left
                renderRect(
                    renderState,
                    middleCoordX + width,
                    middleCoordY - height,
                    width / 2.f,
                    height / 2.f,
                    color);
                //all bottom
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY - height * 2.f,
                    width * 1.5f,
                    height / 2.f,
                    color);
            }
                break;
            case 4: {
                //all right
                renderRect(
                    renderState, 
                    middleCoordX + width,
                    middleCoordY,
                    width / 2,
                    height * 2.5f,
                    color);
                //all middle
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY,
                    width * 1.5f,
                    height / 2.f,
                    color);
                //top half left
                renderRect(
                    renderState, 
                    middleCoordX - width,
                    middleCoordY + height,
                    width / 2,
                    height * 1.5f,
                    color);
            }
                break;
            case 5: {
                //all top
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY + height * 2.f,
                    width * 1.5f,
                    height / 2,
                    color);
                //between top left
                renderRect(
                    renderState,
                    middleCoordX - width,
                    middleCoordY + height,
                    width / 2.f,
                    height / 2.f,
                    color);
                //all middle
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY,
                    width * 1.5f,
                    height / 2.f,
                    color);
                //between bottom right
                renderRect(
                    renderState,
                    middleCoordX + width,
                    middleCoordY - height,
                    width / 2.f,
                    height / 2.f,
                    color);
                //all bottom
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY - height * 2.f,
                    width * 1.5f,
                    height / 2.f,
                    color);
            }
                break;
            case 6: {
                //half right top
                renderRect(
                    renderState,
                    middleCoordX + width / 2.f,
                    middleCoordY + height * 2.f,
                    width,
                    height / 2.f,
                    color);
                //all left
                renderRect(
                    renderState, 
                    middleCoordX - width,
                    middleCoordY,
                    width / 2,
                    height * 2.5f,
                    color);
                //half right middle
                renderRect(
                    renderState,
                    middleCoordX + width / 2.f,
                    middleCoordY,
                    width,
                    height / 2.f,
                    color);
                //between bottom right
                renderRect(
                    renderState,
                    middleCoordX + width,
                    middleCoordY - height,
                    width / 2.f,
                    height / 2.f,
                    color);
                //half right bottom
                renderRect(
                    renderState,
                    middleCoordX + width / 2.f,
                    middleCoordY - height * 2.f,
                    width,
                    height / 2.f,
                    color);
            }
                break;
            case 7: {
                //all top
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY + height * 2.f,
                    width * 1.5f,
                    height / 2,
                    color);
                //all right
                renderRect(
                    renderState, 
                    middleCoordX + width,
                    middleCoordY,
                    width / 2,
                    height * 2.5f,
                    color);
            }
                break;
            case 8: {
                //all left
                renderRect(
                    renderState, 
                    middleCoordX - width,
                    middleCoordY,
                    width / 2,
                    height * 2.5f,
                    color);
                //all right
                renderRect(
                    renderState, 
                    middleCoordX + width,
                    middleCoordY,
                    width / 2,
                    height * 2.5f,
                    color);
                //middle top
                renderRect(
                    renderState, 
                    middleCoordX,
                    middleCoordY + height * 2.f,
                    width,
                    height / 2.f,
                    color);
                //middle middle
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY,
                    width / 2.f,
                    height / 2,
                    color);
                //middle bottom
                renderRect(
                    renderState, 
                    middleCoordX,
                    middleCoordY - height * 2.f,
                    width,
                    height / 2.f,
                    color);
            }  
                break;
            case 9: {
                //top half left
                renderRect(
                    renderState, 
                    middleCoordX - width,
                    middleCoordY + height,
                    width / 2,
                    height * 1.5f,
                    color);
                //middle top
                renderRect(
                    renderState, 
                    middleCoordX,
                    middleCoordY + height * 2.f,
                    width,
                    height / 2.f,
                    color);
                //middle middle
                renderRect(
                    renderState,
                    middleCoordX,
                    middleCoordY,
                    width / 2.f,
                    height / 2,
                    color);
                //all right
                renderRect(
                    renderState, 
                    middleCoordX + width,
                    middleCoordY,
                    width / 2,
                    height * 2.5f,
                    color);
            }
                break;
            default:
                break;
        }

        if(digit == 1)
            middleCoordX -= width * 2.f;
        else
            middleCoordX -= width * 4.f;
    }
}

#pragma endregion

#pragma region BitMap
void setBitMapInfo(
    RenderState& renderState,
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
#pragma endregion