#include "Scene.h"
#include "Windows.h"


bool Scene::GetContinuePgrm() const
{
	return ContinuePgrm;
}

Scene::Scene() : world(Vector2(1, 2)), objectManager(), gm()
{
	ContinuePgrm = true;
}

void Scene::Start()
{
	world.Start();
	objectManager.Start();
	gm.Start();
	world.Render();

}

void Scene::Update()
{


	objectManager.UpdateObjects();  // update objects at the start of the frame


	world.Update(objectManager.GetObjects(), objectManager.GetObjectsCount()); // Always call this method before render
	world.Render(objectManager.GetObjects(), objectManager.GetObjectsCount());

	objectManager.UpdateObjectsPosition(); // Update Object positions

	gm.Update();

	world.Update(objectManager.GetObjects(), objectManager.GetObjectsCount()); // Always call this method before render  
	world.Render(objectManager.GetObjects(), objectManager.GetObjectsCount());


}

void Scene::Exit()
{
	gm.Exit();
	int objectsCount = objectManager.GetObjectsCount();
	GameObject** Objects = objectManager.GetObjects();
	for (int i = 0; i < objectsCount; i++)
	{
		delete Objects[i];
	}
	delete[] Objects;

}

void Scene::GotoXY(int x, int y, Vector2 WorldTopLeft)
{

	COORD scrn{};
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = x + WorldTopLeft.GetX();
	scrn.Y = y + WorldTopLeft.GetY();
	SetConsoleCursorPosition(hConsoleOutput, scrn);
}
void Scene::GotoXY(int x, int y)
{

	COORD scrn{};
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = x;
	scrn.Y = y;
	SetConsoleCursorPosition(hConsoleOutput, scrn);
}

void Scene::LowerString(string& _string)
{
	string result;
	for (char letter : _string) {
		result += tolower(letter);
	}
	_string = result;
}

