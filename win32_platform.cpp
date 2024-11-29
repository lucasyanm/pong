#include <windows.h>
#include "include/renderer.h"
#include "include/macros.h"
#include "include/input.h"
#include "include/game.h"

//callback
LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//win main
GLOBALVAR bool running = true;
GLOBALVAR RenderState renderState;
GLOBALVAR Input input;

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

    float deltaTimeInSeconds = 0.016666f; //60FPS in SPF
    LARGE_INTEGER frameBeginTime;
    QueryPerformanceCounter(&frameBeginTime);

    float performanceFrequency;
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        performanceFrequency = (float)frequency.QuadPart;
    }

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

        simulateGame(input, deltaTimeInSeconds, renderState);

        // Render
        render(renderState, deviceContext);

        // Calculate delta time in seconds
        LARGE_INTEGER frameEndTime;
        QueryPerformanceCounter(&frameEndTime);

        deltaTimeInSeconds = (float)(frameEndTime.QuadPart - frameBeginTime.QuadPart) / performanceFrequency;
        frameBeginTime = frameEndTime;
    }

    return 0;
}

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    int bufferSize;

    resetInput(input);

    switch (uMsg) {
        case WM_CLOSE:
        case WM_DESTROY:
            running = false;
            break;
        case WM_SIZE:
            RECT rectangle;

            GetClientRect(hwnd, &rectangle);

            renderState.width = rectangle.right - rectangle.left;
            renderState.height = rectangle.bottom - rectangle.top;

            allocMemory(renderState);

            setBitMapInfo(
                renderState,
                sizeof(BITMAPINFOHEADER),
                1,
                32,
                BI_RGB
            );
            break;
        case WM_SYSKEYUP:
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
        case WM_KEYUP: { 
            UINT vkCode = (UINT)wParam;
            if (vkCode == VK_ESCAPE) {
                running = false;
            }

            bool pressed = HIWORD(lParam) & KF_UP ? false : true;

            switch (vkCode) {
                processButton(KeyboardButton::UP, VK_UP, pressed);
                processButton(KeyboardButton::DOWN, VK_DOWN, pressed);
                processButton(KeyboardButton::W, 'W', pressed);
                processButton(KeyboardButton::S, 'S', pressed);
                processButton(KeyboardButton::LEFT, VK_LEFT, pressed);
                processButton(KeyboardButton::RIGHT, VK_RIGHT, pressed);
                processButton(KeyboardButton::ENTER, VK_RETURN, pressed);
            }
        }
            break;
        default:
            result = DefWindowProc(
                hwnd,
                uMsg, 
                wParam, 
                lParam);
    }

    return result;
}
