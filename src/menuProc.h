#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <gdiplus.h>

//this file contains functions used in the main file

//	window procedure / behavior
LRESULT CALLBACK WndProcMenuWindow(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	HDC hdc = GetDC(hwnd);
	HCURSOR arrow_cursor = LoadCursorW(0, IDC_ARROW);
	HCURSOR hand_cursor = LoadCursorW(0, IDC_HAND);

	MenuButton newfilebtn = MenuButton(200, 50, NULL, NULL, 600, 600,
		1, 1, NULL, NULL,
		16, 0, L"Comic Sans MS",
		RGB(40, 30, 199), RGB(100, 50, 20), RGB(210, 240, 255), hdc, L"meow");

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

			newfilebtn.drawBox();
			for (int i = 0; i < 600; i++) SetPixel(hdc, i, 290, RGB(0, 0, 0));
			for (int i = 0; i < 600; i++) SetPixel(hdc, 290, i, RGB(0, 0, 0));

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

			if (
					x > newfilebtn.getPosX() && 
					y > newfilebtn.getPosY() &&
					x < (newfilebtn.getPosX() + newfilebtn.getWidth()) &&
					y < (newfilebtn.getPosY() + newfilebtn.getHeight())
				)
			{

				SetWindowText(hwnd, L"uwu");
				SetCursor(hand_cursor);

			}
			else {

				SetCursor(arrow_cursor);

			}

			if (a == MK_CONTROL) SetWindowText(hwnd, L"tft la mia vita");

		}
		break;

		case WM_LBUTTONDOWN:
		{
			short x = LOWORD(lParam);
			short y = HIWORD(lParam);
			std::wstring titolo = L" X: " + std::to_wstring(x) + L" Y: " + std::to_wstring(y);
			SetWindowText(hwnd, titolo.c_str());
			SetCursor(arrow_cursor);

			if (
				x > newfilebtn.getPosX() &&
				y > newfilebtn.getPosY() &&
				x < (newfilebtn.getPosX() + newfilebtn.getWidth()) &&
				y < (newfilebtn.getPosY() + newfilebtn.getHeight())
				)
			{

				OPENFILENAME ofn;
				WCHAR szFile[260] = { 0 };

				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hwnd;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = L"All\0*.*\0MOCprj\0*.MOC\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = L"C:\\Users\\Matteo\\Desktop";
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

				if (GetOpenFileName(&ofn) == TRUE)
				{
					char cStrFile[260];
					wcstombs(cStrFile, szFile, wcslen(szFile) + 1);

					std::string program = "C:\\Users\\Matteo\\Desktop\\prjs\\cpp\\MyOwnCompiler\\x64\\Debug\\MyOwnCompiler.exe";
					std::string parameters = cStrFile;

					// Convert to wide strings
					std::wstring wProgram(program.begin(), program.end());
					std::wstring wParameters(parameters.begin(), parameters.end());

					ShellExecute(NULL, L"open", wProgram.c_str(), wParameters.c_str(), NULL, SW_SHOW);

					ExitProcess(69);
				}

			}

			if (
				x > 0 &&
				y > 0 &&
				x < 200 &&
				y < 200
				)
			{

				OPENFILENAME ofn;
				WCHAR szFile[260] = { 0 };

				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hwnd;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = L"All\0*.*\0MOCprj\0*.MOC\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
				SetCurrentDirectory(L"C:\\Users\\Matteo\\Desktop");
				ofn.lpstrInitialDir = L"C:\\Users\\Matteo\\Desktop";

				// Reset the initial directory each time before calling GetSaveFileName
				SetCurrentDirectory(L"C:\\Users\\Matteo\\Desktop");

				// Call GetSaveFileName

				ofn.lpstrInitialDir = L"C:\\Users\\Matteo\\Desktop";

				if (GetSaveFileName(&ofn) == TRUE)
				{

					ofn.lpstrInitialDir = L"C:\\Users\\Matteo\\Desktop";

					// Check the file extension
					std::wstring ws(szFile);
					std::string str(ws.begin(), ws.end());
					size_t ext_pos = str.find_last_of(".");
					std::string ext = (ext_pos == std::string::npos) ? "" : str.substr(ext_pos);

					// If the file has no extension or the user selected "MOCprj", append ".MOC"
					if (ext.empty() || ofn.nFilterIndex == 2) str += ".MOC";

					// Convert back to wide string
					std::wstring wstr(str.begin(), str.end());
					wcscpy(szFile, wstr.c_str());

					HANDLE hFile = CreateFile(szFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					if (hFile == INVALID_HANDLE_VALUE)
					{
						// Handle the error
					}
					else
					{
						// Use the file
						CloseHandle(hFile);
					}

					char cStrFile[260];
					wcstombs(cStrFile, szFile, wcslen(szFile) + 1);

					DestroyWindow(hwnd);

					std::string program = "C:\\Users\\Matteo\\Desktop\\prjs\\cpp\\MyOwnCompiler\\x64\\Debug\\MyOwnCompiler.exe";
					std::string parameters = cStrFile;

					// Convert to wide strings
					std::wstring wProgram(program.begin(), program.end());
					std::wstring wParameters(parameters.begin(), parameters.end());

					ShellExecute(NULL, L"open", wProgram.c_str(), wParameters.c_str(), NULL, SW_SHOW);

					ExitProcess(69);
				}

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