#include "Scene.h"
#include "Windows.h"
#include "Application.h"


GameManager Scene::gm = GameManager();
bool Scene::GetContinuePgrm() const
{
	return ContinuePgrm;
}

Scene::Scene() : world(Vector2(1, 2), 16, 10), objectManager()
{
	ContinuePgrm = true;
}

void Scene::Start()
{
	Application::DrawBG();
	world.Start();
	objectManager.Start();
	gm.Start();

	world.Render();
}

void Scene::Update()
{
	objectManager.UpdateObjects();  // update objects at the start of the frame
}

void Scene::UpdateGameObjectsPos()
{
	objectManager.UpdatePositions(); 
}

void Scene::Render()
{
	world.Update(objectManager.GetObjects(), objectManager.GetObjectsCount()); // Always call this method before render  
	world.Render(objectManager.GetObjects(), objectManager.GetObjectsCount());


}

void Scene::Exit()
{
	int objectsCount = objectManager.GetObjectsCount();
	GameObject** Objects = objectManager.GetObjects();
	for (int i = 0; i < objectsCount; i++)
	{
		delete Objects[i];
	}
	delete[] Objects;

	gm.Exit();
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

void Scene::ChangeColor(TypeColor color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	//for (int k = 1; k < 255; k++)
	//{
	//	// pick the colorattribute k you want
	//	SetConsoleTextAttribute(hConsole, k);
	//	cout << k << " I want to be nice today!" << endl;
	//}

	switch (color)
	{
	case Scene::Red:
		SetConsoleTextAttribute(hConsole, 460);
		break;
	case Scene::Green:
		SetConsoleTextAttribute(hConsole, 426);
		break;
	case Scene::Blue:
		SetConsoleTextAttribute(hConsole, 409);
		break;
	case Scene::Purple:
		SetConsoleTextAttribute(hConsole, 477);
		break;
	case Scene::Yellow:
		SetConsoleTextAttribute(hConsole, 102);
	case Scene::Black:
		SetConsoleTextAttribute(hConsole, 0);
		break;
	
	case Scene::White:
		SetConsoleTextAttribute(hConsole, 119);
		break;
	case Scene::BG_COLOR:
		SetConsoleTextAttribute(hConsole, 136);
		break;
	default:
		SetConsoleTextAttribute(hConsole, 7);
		break;
	}
}

void Scene::ChangeColor(TypeColor color, bool tochar)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	//for (int k = 1; k < 255; k++)
	//{
	//	// pick the colorattribute k you want
	//	SetConsoleTextAttribute(hConsole, k);
	//	cout << k << " I want to be nice today!" << endl;
	//}

	switch (color)
	{
	case Scene::Red:
		SetConsoleTextAttribute(hConsole, 12); 
		break;
	case Scene::Green:
		SetConsoleTextAttribute(hConsole, 10);
		break;
	case Scene::Blue:
		SetConsoleTextAttribute(hConsole, 7);
		break;
	case Scene::Purple:
		SetConsoleTextAttribute(hConsole, 5);
		break;
	case Scene::Yellow:
		SetConsoleTextAttribute(hConsole, 14);
	case Scene::Black:
		SetConsoleTextAttribute(hConsole, 0);
		break;
	
	case Scene::White:
		SetConsoleTextAttribute(hConsole, 15);
		break;
	default:
		SetConsoleTextAttribute(hConsole, 7);
		break;
	}
}
void Scene::ChangeColor(const int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Scene::LowerString(string& _string)
{
	string result;
	for (char letter : _string) {
		result += tolower(letter);
	}
	_string = result;
}

