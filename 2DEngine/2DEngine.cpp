// 2DEngine.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

int main(int argc, char** argv)
{
	FreeConsole();
	UserWindow uw(L"UserWindow", L"WindowGame", 0, 0, 800, 600);
	uw.Create();
	uw.Register();
	uw.Show();
	uw.Run();
	return 0;
}

