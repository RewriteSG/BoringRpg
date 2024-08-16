#include "ClockSprite.h"
#include "World.h"
#include "Scene.h"
#include <iostream>

void ClockSprite::Render(int x, int y, Vector2 topLeft)
{

	Scene::GotoXY(2 + x + (CellX * x), 4 + y + (y * CellY), topLeft);
	Scene::ChangeColor(Scene::Red,true);
	std::cout << "~~~~";

	Scene::ChangeColor(Scene::Default);
}
