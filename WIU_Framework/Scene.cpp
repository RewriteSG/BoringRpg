#include "Scene.h"
#include "Windows.h"
#include "Application.h"


GameManager Scene::gm = GameManager();
bool Scene::GetContinuePgrm() const
{
	return ContinuePgrm;
}

Scene::Scene() : world(Vector2(33, 2), 16, 10), objectManager()
{
	ContinuePgrm = true;
	name = " ";
}

ObjectManager* Scene::GetObjectManager()
{
	return &objectManager;
}

void Scene::Start()
{
	//Application::DrawBG();
	world.Start();
	objectManager.Start();
	gm.Start();

	world.Render();

	UI gameUI(Vector2(150, 12), 0, 45);
	gameUI.CreateBox(Vector2(-5, -7), "Objective:", 6);
	gameUI.CreateBox(Vector2(-5, 0), "Inventory:", 10);
	//gameUI.CreateText("Axiety Meter: ", Vector2(20, -9));
	gameUI.CreateText("YOU AT: " + getName(), Vector2(-5, -9));

	UI gameUI2(Vector2(Application::numberOfColumns / 2 - 171 / 2, 35), 0, 171);
	gameUI2.CreateBox(Vector2(), "", 13);
}

void Scene::Update()
{
	objectManager.UpdateObjects();  // update objects at the start of the frame
	Render();

	UpdateGameObjectsPos();

	gm.Update();
	Render();
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

std::string Scene::tolowerString(std::string& _string)
{
	std::string text{};
	for (char& ch : _string)
		text += tolower(ch);
	return text;
}

void Scene::DrawASCII_Art(string ascii_art, int x, int y, int color)
{
	int indexY = 0;
	for (int i = 0; i < ascii_art.length(); i++)
	{

		GotoXY(x, y+indexY, SceneManager::currentScene->world.GetTopLeft());
		for (int x = i; x < ascii_art.length(); x++)
		{
			char test = ascii_art[x];
			if (ascii_art[x] == '\n') 
			{
				indexY++; 
				i = x;
				break;
			}
			else
			{
				cout<<ascii_art[x]; 
			}
			if ((x + 1 == ascii_art.length()))
			{
				i = ascii_art.length();
			}

		}
	}

}

std::string Scene::getName(void) const { return name; }

