#include "stdafx.h"

std::map<HWND, UserWindow*> windows;

UserWindow::UserWindow(LPCWSTR title, LPCWSTR uniqueClassName, int x, int y, int width, int height)
{
	this->title = title;
	this->uniqueClassName = uniqueClassName;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->renderer.InitBackbuffer(width, height);
}

void UserWindow::Run()
{
	HACCEL hAccelTable = LoadAccelerators(NULL, MAKEINTRESOURCE(IDC_2DENGINE));
	MSG msg;

	while (windows.size() > 0)
	{
		while (GetMessage(&msg, nullptr, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
}

BOOL UserWindow::Create()
{
	RegisterUserWindow();
	this->hWnd = InitInstance();
	return this->hWnd != NULL;
}

void UserWindow::Register()
{
	windows.insert(std::pair<HWND, UserWindow*>(this->hWnd, this));
}

void UserWindow::Show()
{
	ShowWindow(this->hWnd, true);
	UpdateWindow(this->hWnd);
}

HWND UserWindow::GetHandler()
{
	return this->hWnd;
}

HWND UserWindow::InitInstance()
{
	HWND hWnd = CreateWindowEx(WS_EX_RIGHT, uniqueClassName, title, WS_OVERLAPPEDWINDOW,
							   x, y, width, height,
							   GetDesktopWindow(), NULL, NULL, NULL);

	if (!hWnd)
	{
		return NULL;
	}

	return hWnd;
}

ATOM UserWindow::RegisterUserWindow()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = UserWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = NULL;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = this->uniqueClassName;
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassExW(&wcex);
}

LRESULT CALLBACK UserWindow::RealWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BITMAP bm;
			HBITMAP newBm = this->renderer.GetBackbuffer();
			HDC hdc = BeginPaint(hWnd, &ps);
			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, newBm);
			GetObject(newBm, sizeof(bm), &bm);
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hbmOld);
			DeleteDC(hdcMem);
			EndPaint(hWnd, &ps);
			this->renderer.InitBackbuffer(this->width, this->height);
		}
		break;
		case WM_DESTROY:
			windows.erase(hWnd);
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT UserWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (windows.count(hwnd))
	{
		UserWindow* me = windows.at(hwnd);
		return me->RealWndProc(hwnd, msg, wParam, lParam);
	}
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

GraphicRenderer UserWindow::GetRenderer()
{
	return this->renderer;
}

LPCWSTR UserWindow::GetTitle()
{
	return this->title;
}

LPCWSTR UserWindow::GetUniqueClassName()
{
	return this->uniqueClassName;
}

int UserWindow::GetX()
{
	return this->x;
}

int UserWindow::GetY()
{
	return this->y;
}

int UserWindow::GetWidth()
{
	return this->width;
}

int UserWindow::GetHeight()
{
	return this->height;
}
