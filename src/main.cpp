#include "include.h"

const int WINDOWWIDTH = 800, WINDOWHEIGHT = 600, WINDOWPOSX = 400, WINDOWPOSY = 150;

void drawBox(
	HDC hdc, HWND hwnd, LPCWSTR text, HFONT font, COLORREF color,
	int width, int height, _In_opt_ int posx, _In_opt_ int posy
) {

	SelectObject(hdc, font);

	if (posx == NULL) posx = WINDOWWIDTH / 2;
	if (posy == NULL) posy = WINDOWHEIGHT / 2;

	//box 1 = new file
	for (int i = 0; i < ( width / 2 ); i++) SetPixel(hdc, posx - i, posy, color);
	for (int i = 0; i < (width / 2); i++) SetPixel(hdc, posx + i, posy, color);
	for (int i = 0; i < height; i++) SetPixel(hdc, posx - 105, posy + i, color);
	for (int i = 0; i < height; i++) SetPixel(hdc, posx + 105, posy + i, color);
	for (int i = 0; i < (width / 2); i++) SetPixel(hdc, posx - i, posy + height, color);
	for (int i = 0; i < (width / 2); i++) SetPixel(hdc, posx + i, posy + height, color);

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
	RECT rect = { posx - (width/2), posy,  posx + (width / 2), posy + height};
	DrawText(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	HDC hdc = GetDC(hwnd);

	switch (msg) {

		case WM_CREATE:
		{

			SetTimer(hwnd, 1, 20, NULL);

		}
		break;

		case WM_TIMER:
		{

			//

		}
		break;

		case WM_PAINT:
		{

			HFONT font = CreateFontW(28, 0, 0, 0,
				FW_EXTRALIGHT, FALSE, FALSE, FALSE,
				ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE, L"Comic Sans MS");

			drawBox(hdc, hwnd, L"new file", font, RGB(150, 120, 30), 210, 50, NULL, 30);
			drawBox(hdc, hwnd, L"open file", font , RGB(150, 120, 30), 210, 50, NULL, 120);

		}
		break;

		case WM_DROPFILES:
		{
			const wchar_t* a = L"default value";

			HDROP hDrop = (HDROP)wParam;
			UINT nNumFilesDropped = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);

			for (UINT i = 0; i < nNumFilesDropped; i++)
			{
				TCHAR szFilePath[MAX_PATH];
				DragQueryFile(hDrop, i, szFilePath, MAX_PATH);

				a = szFilePath;
				char buffer[1024];
				wcstombs(buffer, a, sizeof(buffer));
			}

			std::wcout << a << std::endl;

			DragFinish(hDrop);

		}
		break;

		case WM_MOUSEMOVE:
		{

			WPARAM a = wParam;
			short x = LOWORD(lParam);
			short y = HIWORD(lParam);
			if (a == MK_CONTROL) {

				std::wstring titolo = L" X: " + std::to_wstring(x) + L" Y: " + std::to_wstring(y);
				SetWindowText(hwnd, titolo.c_str());

			}
			
			else if (x > ((WINDOWWIDTH / 2) - 105) && x < ((WINDOWWIDTH / 2) + 105) && y > 30 && y < 80) {

				SetWindowText(hwnd, L"uwu");
				HCURSOR cursor = LoadCursorW(0, IDC_HAND);
				SetCursor(cursor);

			}
			else {

				SetWindowText(hwnd, L"bau");
				HCURSOR cursor = LoadCursorW(0, IDC_ARROW);
				SetCursor(cursor);

			}

		}
		break;

		case WM_LBUTTONDOWN:
		{
			short x = LOWORD(lParam);
			short y = HIWORD(lParam);
			std::wstring titolo = L" X: " + std::to_wstring(x) + L" Y: " + std::to_wstring(y);
			SetWindowText(hwnd, titolo.c_str());
			if (x > ((WINDOWWIDTH / 2) - 105) && x < ((WINDOWWIDTH / 2) + 105) && y > 30 && y < 80) {

				SetWindowText(hwnd, L"meow");
				HCURSOR cursor = LoadCursorW(0, IDC_HAND);
				SetCursor(cursor);

			}
			else {

				HCURSOR cursor = LoadCursorW(0, IDC_ARROW);
				SetCursor(cursor);

			}

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

int main(int argc, char* argv[], char* env[]) {

	HINSTANCE hInstance = GetModuleHandle(NULL);
	LPSTR lpCmdLine = NULL;
	char defaultvalue[] = "default value";
	char* argument1 = argv[1];

	return WinMain(hInstance, NULL, lpCmdLine, SW_SHOW);
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {

	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (argc >= 2) {
		char buffer[1024];  // Make sure the buffer is large enough
		wcstombs(buffer, argv[1], sizeof(buffer));
		char* argument1 = buffer;

		std::cout << argument1 << " 1" << std::endl;
	}

	const auto pClassName = L"title";

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowEx(

		WS_EX_ACCEPTFILES | WS_EX_APPWINDOW, pClassName,
		L"window name",
		WS_CAPTION | WS_SYSMENU,
		WINDOWPOSX, WINDOWPOSY, WINDOWWIDTH, WINDOWHEIGHT,
		nullptr, nullptr, hInstance, nullptr

	);

	ShowWindow(hWnd, SW_SHOW);

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