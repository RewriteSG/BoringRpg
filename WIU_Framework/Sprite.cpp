#include "Sprite.h"
#include "Application.h"
#include "World.h"
#include <iostream>
using namespace std;
Sprite::Sprite()
{

}

void Sprite::Render(int x, int y, Vector2 topLeft)
{
	//Scene::GotoXY(x, y, topLeft);
	for (int i = 0; i <= CellY; i++)
	{
		Scene::GotoXY(x + (CellX * x), i+ y + (y * CellY), topLeft);
		for (int x = 0; x <= CellX; x++)
		{
			std::cout << "*";
		}
	}
}

void Sprite::RenderVoid(int x, int y, Vector2 topLeft)
{

	//Scene::GotoXY(x, y, topLeft);
	for (int i = 0; i < CellY; i++)
	{
		Scene::GotoXY(x, i+y + CellY, topLeft);

		std::cout << ".";
		for (int x = 0; x < CellX; x++)
		{
			if (i == 0)
				std::cout << ".";
			else

				std::cout << " ";
		}
	}
}
