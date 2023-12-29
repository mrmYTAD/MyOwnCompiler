#include "include.h"
#include "menuProc.h"
#include "compilerProc.h"
//	entry point and window handler for the engine starting window.

//	entry point ( console ), takes arguments and return them to "WinMain"
int main(int argc, char* argv[], char* env[]) {

    HINSTANCE hInstance = GetModuleHandle(NULL);
    LPSTR lpCmdLine = NULL;

    return WinMain(hInstance, NULL, lpCmdLine, SW_SHOW);
}

//	graphics entry point, executed after main, here the window is created, and messages are sent to the system ( so to the window procedure too )
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow
) {
    int argc;
    char* passedarg;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    // If a parameter is passed, open the project editor window
    if (argc >= 2) {

        char buffer[1024];
        wcstombs(buffer, argv[1], sizeof(buffer));
        passedarg = buffer;

        WNDCLASSEX windowClass = { 0 };
        windowClass.cbSize = sizeof(windowClass);
        windowClass.style = 0x0020; //CS_OWNDC
        windowClass.lpfnWndProc = WndProcEngineWindow;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = hInstance;
        windowClass.hIcon = nullptr;
        windowClass.hCursor = nullptr;
        windowClass.hbrBackground = nullptr;
        windowClass.lpszMenuName = nullptr;
        windowClass.hIconSm = nullptr;
        windowClass.lpszClassName = L"ProjectEditorClassName";

        RegisterClassEx(&windowClass);

        HWND hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_ACCEPTFILES,
            windowClass.lpszClassName, L"Project Editor",
            WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME,
            500, 100, 600, 600,
            nullptr, nullptr, windowClass.hInstance, nullptr);
        RegisterClassEx(&windowClass);

        ShowWindow(hwnd, 10);

        std::cout << passedarg << std::endl;

    }

    // Else open the menu window
    else {

        WNDCLASSEX windowClass = { 0 };
        windowClass.cbSize = sizeof(windowClass);
        windowClass.style = 0x0020; //CS_OWNDC
        windowClass.lpfnWndProc = WndProcMenuWindow;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = hInstance;
        windowClass.hIcon = nullptr;
        windowClass.hCursor = nullptr;
        windowClass.hbrBackground = nullptr;
        windowClass.lpszMenuName = nullptr;
        windowClass.hIconSm = nullptr;
        windowClass.lpszClassName = L"MenuWindowClassName";

        RegisterClassEx(&windowClass);

        HWND hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_ACCEPTFILES,
            windowClass.lpszClassName, L"MOGE menu",
            WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU,
            500, 100, 600, 600,
            nullptr, nullptr, windowClass.hInstance, nullptr);

        ShowWindow(hwnd, 10);

    }

    MSG msg;
    BOOL gResult;

    while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (gResult == -1) {
        return -1;
    }
    else {
        return msg.wParam;
    }

    return 0;
}
