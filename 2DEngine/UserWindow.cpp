#include "stdafx.h"

UserWindow* me = NULL;

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
	HBITMAP bmpRed = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
	HBITMAP bmpGreen = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3));
	
	this->run = true;
	DWORD previous = GetTickCount();
	int x = 0;
	while (this->run)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		this->Draw(bmpGreen, BitmapRectangle(x++, x++, 800, 600));
		while (GetTickCount() - previous < 15);
		this->DrawWindow();
		previous = GetTickCount();
	}
}

void UserWindow::DrawWindow()
{
	BITMAP bm;
	HBITMAP newBm = this->renderer.GetBackbuffer();
	HDC hdc = GetDC(hWnd);
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, newBm);
	GetObject(newBm, sizeof(bm), &bm);
	BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
	ReleaseDC(hWnd, hdc);
	this->renderer.InitBackbuffer(this->width, this->height);
}

BOOL UserWindow::Create()
{
	RegisterUserWindow();
	this->hWnd = InitInstance();
	return this->hWnd != NULL;
}

void UserWindow::Register()
{
	me = this;
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
			HDC hDC = BeginPaint(hWnd, &ps);
			// other draw code here.
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			this->run = false;
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT UserWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (me != NULL)
		return me->RealWndProc(hwnd, msg, wParam, lParam);
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}


void UserWindow::Draw(HBITMAP bmp, BitmapRectangle rect)
{
	this->renderer.Draw(bmp, rect);
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