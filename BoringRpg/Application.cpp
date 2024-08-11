#include "Application.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include <iostream>

int main() {
	Application app;
	app.sceneMgr.Start();
	app.sceneMgr.Update();
	app.sceneMgr.Exit();
	return 0;
}
Application::Application()
{
	sceneMgr;
}