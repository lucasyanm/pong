#include <windows.h>

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

bool running = true;

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
        // Render
    }

    return 0;
}

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch (uMsg) {
        case WM_CLOSE:
        case WM_DESTROY:
            running = false;
            break;
        default:
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return result;
}
