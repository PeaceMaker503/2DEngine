// 2DEngine.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

int main(int argc, char** argv)
{
	FreeConsole();
	HINSTANCE hInstance = NULL;
	UserWindow uw(L"UserWindow", L"WindowGame", 0, 0, 800, 600);
	UserWindow uw2(L"UserWindow2", L"WindowGame2", 0, 0, 400, 200);
	uw.Create();
	uw.Register();
	uw.Show();
	uw2.Create();
	uw2.Register();
	uw2.Show();
	UserWindow::Run();
	return 0;
}