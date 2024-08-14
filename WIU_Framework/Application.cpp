#include "Application.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include <iostream>
#include "Windows.h"

void Application::FontSize(const Vector2 size)
{
	CONSOLE_FONT_INFOEX fontex{sizeof(CONSOLE_FONT_INFOEX) };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, false, &fontex);
	fontex.dwFontSize.X = size.GetX(); // Width of each character in pixels
	fontex.dwFontSize.Y = size.GetY(); // Height of each character in pixels
	SetCurrentConsoleFontEx(hOut, false, &fontex);
}
void Application::ScreenSMaximised(void) 
{
	// Get the console window handle
	HWND consoleWindow = GetConsoleWindow();
	// Maximize the console window
	ShowWindow(consoleWindow, SW_MAXIMIZE);
}
void Application::HideCursor(void)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = FALSE; // Set the cursor visibility to false
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

Application::Application(void) { sceneMgr = new SceneManager(); }

void Application::Init(void)
{
	FontSize(Vector2(9, 18));
	ScreenSMaximised();
	HideCursor();

	for (int i = 0; i < 43; ++i)
	{
		for (int j = 0; j < 172; ++j)
		{
			Scene::ChangeColor(Scene::BG_COLOR);
			std::cout << " ";
		}
		std::cout << std::endl;
	}

	sceneMgr->Start();
}

void Application::Update(void)
{
	do
	{
		sceneMgr->Update();
	} while (SceneManager::currentScene);
}

void Application::Exit(void) { delete sceneMgr; }
