#include <windows.h>
#include "include/renderer.h"
#include "include/macros.h"
#include "include/input.h"

//TODO: ReadMe file
//TODO: Cite make as needed to build on a readme file

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
        clearScreen(renderState, 0x00ff00);

        if(input.buttons[Button::UP].pressed) {
            renderRect(renderState, 300, 300, 200, 200, 0xff0000);
        }
        if(input.buttons[Button::DOWN].pressed) {
            renderRect(renderState, 500, 500, 200, 200, 0xff0000);
        }
        if(input.buttons[Button::LEFT].pressed) {
            clearScreen(renderState, 0xff0000);
        }

        // Render
        render(renderState, deviceContext);
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
                case VK_UP:
                    input.buttons[Button::UP].pressed = pressed;
                    input.buttons[Button::UP].changed = true;
                    break;
                case VK_DOWN:
                    input.buttons[Button::DOWN].pressed = pressed;
                    input.buttons[Button::DOWN].changed = true;
                    break;
                case VK_LEFT:
                    input.buttons[Button::LEFT].pressed = pressed;
                    input.buttons[Button::LEFT].changed = true;
                    break;
                case VK_RIGHT:
                    input.buttons[Button::RIGHT].pressed = pressed;
                    input.buttons[Button::RIGHT].changed = true;
                    break;
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
