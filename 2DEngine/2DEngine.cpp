// 2DEngine.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

int main(int argc, char** argv)
{
	FreeConsole();
	UserWindow uw(L"UserWindow", L"WindowGame", 0, 0, 800, 600);
	HBITMAP bmpRed = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
	uw.GetRenderer().Draw(bmpRed);
	uw.Create();
	uw.Register();
	uw.Show();
	UserWindow::Run();
	return 0;
}

