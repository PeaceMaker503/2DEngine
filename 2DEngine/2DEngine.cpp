// 2DEngine.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdafx.h"

int main(int argc, char** argv)
{
	FreeConsole();
	UserWindow uw(L"UserWindow", L"WindowGame", 0, 0, 800, 600);
	HBITMAP bmpRed = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
	HBITMAP bmpGreen = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3));
	uw.Draw(bmpRed, BitmapRectangle(200,200,800,600));
	uw.Draw(bmpGreen, BitmapRectangle(0, 0, 800, 600));
	uw.Create();
	uw.Register();
	uw.Show();
	UserWindow::Run();
	return 0;
}

