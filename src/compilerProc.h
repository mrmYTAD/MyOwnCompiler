#define _CRT_SECURE_NO_WARNINGS

LRESULT CALLBACK WndProcEngineWindow(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {

    case WM_CREATE:
    {

        SetTimer(hwnd, 1, 500, NULL);

    }
    break;

    case WM_TIMER:
    {

        std::cout << "uwu" << std::endl;

    }
    break;

    case WM_CLOSE:
    {

        PostQuitMessage(69);

    }
    break;

    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}