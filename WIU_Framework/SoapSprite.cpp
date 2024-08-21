#include "SoapSprite.h"
#include "World.h"
#include "Scene.h"
#include <iostream>
void SoapSprite::Render(int x, int y, Vector2 topLeft)
{

	Scene::GotoXY(0 + x + (CellX * x), 0 + y + (y * CellY), topLeft);
	Scene::ChangeColor(Scene::Cyan, true);
	std::cout << "B BBBB B";

	Scene::GotoXY(0 + x + (CellX * x), 1 + y + (y * CellY), topLeft);
	std::cout << "BBBBB BB";
	Scene::GotoXY(0 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << "  BBBBB ";
	Scene::GotoXY(0 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << " BB BB B"; 

	Scene::ChangeColor(Scene::Default);
}
