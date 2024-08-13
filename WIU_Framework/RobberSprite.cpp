#include "RobberSprite.h"
#include "World.h"
#include "Scene.h"
#include <iostream>
void RobberSprite::Render(int x, int y, Vector2 topLeft)
{

Scene::GotoXY(x + (CellX * x), 0 + y + (y * CellY), topLeft);
std::cout << " ";


Scene::GotoXY(3 + x + (CellX * x), 0 + y + (y * CellY), topLeft);
Scene::ChangeColor(Scene::Red);
std::cout << "GG";

Scene::GotoXY(1 + x + (CellX * x), 1 + y + (y * CellY), topLeft);
std::cout << "GGGGGG";

Scene::GotoXY(0 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
std::cout << "G";
Scene::GotoXY(2 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
std::cout << "GGGG";
Scene::GotoXY(7 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
std::cout << "G";
Scene::GotoXY(2 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
std::cout << "G";
Scene::GotoXY(5 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
std::cout << "G";
Scene::ChangeColor(Scene::Default);
}
