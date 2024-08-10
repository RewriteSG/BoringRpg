#include "Application.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include <iostream>

int main() {
	return 0; 
}
Application::Application()
{
}
void Application::Start()
{
	scene = Scene();
	srand((unsigned int)time(0));
	scene.Start();
	//_CrtDumpMemoryLeaks();
}

void Application::Update()
{
	scene.Update();
}

void Application::Exit()
{
	scene.Exit();
}