#include "Application.h"

int main(void) {
	Application app;
	app.Init();
	app.Update();
	app.Exit();
	exit(0);
	return 0;
}