#include "Application.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include <iostream>
#include "Windows.h"

int Application::numberOfColumns = 0;
int Application::numberOfRows = 0;

void Application::FontSize(const Vector2 size)
{
	CONSOLE_FONT_INFOEX fontex{sizeof(CONSOLE_FONT_INFOEX) };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, false, &fontex);
	fontex.dwFontSize.X = size.GetX(); // Width of each character in pixels
	fontex.dwFontSize.Y = size.GetY(); // Height of each character in pixels
	SetCurrentConsoleFontEx(hOut, false, &fontex);
}
void Application::ScreenMaximised(void) 
{
	// Get the console window handle
	HWND consoleWindow = GetConsoleWindow();
	// Maximize the console window
	ShowWindow(consoleWindow, SW_MAXIMIZE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	// Get the console screen buffer info
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	numberOfColumns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	numberOfRows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
void Application::HideCursor(void)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = FALSE; // Set the cursor visibility to false
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void Application::ShowCursor(void)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = TRUE; // Set the cursor visibility to false
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
Application::Application(void) { 
	sceneMgr = new SceneManager(); 
}

void Application::Init(void)
{
	FontSize(Vector2(7, 16));
	ScreenMaximised();
	HideCursor();
}

void Application::Update(void)
{
	sceneMgr->Start();
	do
	{
		sceneMgr->Update();
	} while (SceneManager::currentScene);
}

void Application::Exit(void) { delete sceneMgr; }
