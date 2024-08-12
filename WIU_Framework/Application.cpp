#include "Application.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include <iostream>
#include "Windows.h"

int main() {
	Application app;
	app.sceneMgr.Start();
	while(true)
	app.sceneMgr.Update();
	app.sceneMgr.Exit();
	return 0;
}
Application::Application()
{

	std::cout << "Test: ";
	// Get the console window handle
	HWND consoleWindow = GetConsoleWindow();


	// Maximize the console window
	ShowWindow(consoleWindow, SW_MAXIMIZE);

	CONSOLE_FONT_INFOEX fontex{ sizeof(CONSOLE_FONT_INFOEX) };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hOut == INVALID_HANDLE_VALUE) {
		std::cerr << "Error: Unable to get console handle." << std::endl;
	}

	if (GetCurrentConsoleFontEx(hOut, false, &fontex)) {

		fontex.dwFontSize.X = 9; // Width of each character in pixels
		fontex.dwFontSize.Y = 14; // Height of each character in pixels

		
		if (SetCurrentConsoleFontEx(hOut, false, &fontex)) {
			std::cout << "Working";
		
		}

	}
	sceneMgr;
}