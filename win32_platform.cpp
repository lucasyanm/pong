#include <windows.h>
#include "include/renderer.h"
#include "include/macros.h"

//TODO: ReadMe file
//TODO: Cite make as needed to build on a readme file

//callback
LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//win main
GLOBALVAR bool running = true;

int WINAPI wWinMain(
    HINSTANCE hInstance, 
    HINSTANCE hPrevInstance, 
    PWSTR pCmdLine, 
    int nCmdShow
) {
    const wchar_t CLASS_NAME[] = L"Game Window Class";

    WNDCLASSW WindowClass = {};
    WindowClass.style = CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpszClassName = CLASS_NAME;
    WindowClass.lpfnWndProc = WindowCallback;

    RegisterClassW(&WindowClass);

    HWND window = CreateWindowW(
        WindowClass.lpszClassName, 
        L"My First Game", 
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        1280, 720, 
        NULL, 
        NULL, 
        hInstance, 
        NULL);

    HDC deviceContext = GetDC(window);

    while(running)
    {
        // Input
        MSG message;
        while(PeekMessageW(
            &message,
            window,
            0,
            0,
            PM_REMOVE
        )) {
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
        // Update
        Renderer::clearScreen(0x00ff00);
        Renderer::renderRect(300, 300, 200, 200, 0xff0000);
        Renderer::renderRect(0, 0, 100, 100, 0x0000ff);
        // renderRect(.5, .5, .2, .2, 0xff0000);

        // Render
        StretchDIBits(
            deviceContext,
            0, 0, Renderer::renderState.width, Renderer::renderState.height,
            0, 0, Renderer::renderState.width, Renderer::renderState.height,
            Renderer::renderState.memory,
            &Renderer::renderState.bitMapInfo,
            DIB_RGB_COLORS,
            SRCCOPY);
    }

    return 0;
}

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    int bufferSize;

    switch (uMsg) {
        case WM_CLOSE:
        case WM_DESTROY:
            running = false;
            break;
        case WM_SIZE:
            RECT rectangle;

            GetClientRect(hwnd, &rectangle);

            Renderer::renderState.width = rectangle.right - rectangle.left;
            Renderer::renderState.height = rectangle.bottom - rectangle.top;

            bufferSize = Renderer::renderState.width 
                * Renderer::renderState.height 
                * sizeof(UINT32);

            if(Renderer::renderState.memory)
                VirtualFree(Renderer::renderState.memory, 0, MEM_RELEASE);

            Renderer::renderState.memory = VirtualAlloc(
                NULL, 
                bufferSize, 
                MEM_COMMIT | MEM_RESERVE, 
                PAGE_READWRITE
            );

            Renderer::renderState.bitMapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            Renderer::renderState.bitMapInfo.bmiHeader.biWidth = Renderer::renderState.width;
            Renderer::renderState.bitMapInfo.bmiHeader.biHeight = Renderer::renderState.height;
            Renderer::renderState.bitMapInfo.bmiHeader.biPlanes = 1;
            Renderer::renderState.bitMapInfo.bmiHeader.biBitCount = 32;
            Renderer::renderState.bitMapInfo.bmiHeader.biCompression = BI_RGB;

            break;
        default:
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return result;
}
