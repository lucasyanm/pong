#include <windows.h>
// HACK: Change to module
#include "renderer.cpp"

//callback
LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//win main
GLOBALVAR bool running = true;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
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
        clearScreen(0x00ff00);
        renderRect(200, 50, 400, 500, 0xff0000);

        // Render
        StretchDIBits(
            deviceContext,
            0, 0, renderState.width, renderState.height,
            0, 0, renderState.width, renderState.height,
            renderState.memory,
            &renderState.bitMapInfo,
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

            renderState.width = rectangle.right - rectangle.left;
            renderState.height = rectangle.bottom - rectangle.top;

            bufferSize = renderState.width * renderState.height * sizeof(UINT32);

            if(renderState.memory)
                VirtualFree(renderState.memory, 0, MEM_RELEASE);

            renderState.memory = VirtualAlloc(NULL, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            renderState.bitMapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            renderState.bitMapInfo.bmiHeader.biWidth = renderState.width;
            renderState.bitMapInfo.bmiHeader.biHeight = renderState.height;
            renderState.bitMapInfo.bmiHeader.biPlanes = 1;
            renderState.bitMapInfo.bmiHeader.biBitCount = 32;
            renderState.bitMapInfo.bmiHeader.biCompression = BI_RGB;

            break;
        default:
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return result;
}
