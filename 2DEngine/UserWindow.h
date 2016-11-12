#pragma once

#include "stdafx.h"

class UserWindow
{
	public:
		LPCWSTR UserWindow::GetTitle();
		LPCWSTR UserWindow::GetUniqueClassName();
		int UserWindow::GetX();
		int UserWindow::GetY();
		int UserWindow::GetWidth();
		int UserWindow::GetHeight();
		HWND UserWindow::GetHandler();
		UserWindow::UserWindow(LPCWSTR title, LPCWSTR uniqueClassName, int x, int y, int width, int height);
		BOOL UserWindow::Create();
		void UserWindow::Show();
		void UserWindow::Register();
		static void UserWindow::Run();
	private:
		LPCWSTR title;
		LPCWSTR uniqueClassName;
		int x;
		int y;
		int width;
		int height;
		HWND hWnd;
		HWND InitInstance();
		ATOM RegisterUserWindow();
		LRESULT CALLBACK RealWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};