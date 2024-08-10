#include "World.h"
#include "Scene.h"
#include <iostream>
#include "ObjectManager.h"
using namespace std;
World* World::worldInstance = nullptr;

World* World::GetWorldInstance()
{
	return worldInstance;
}
World::World(Vector2 topLeft) : topLeftPos(topLeft), botRightPos(topLeft + Vector2(10,10))
{
	worldInstance = this;
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			charMap[y][x] = '.';
		}
	}
}
void World::Start()
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			charMap[y][x] = '.';
		}
	}
}
//
//const char World::GetCharFromXandY(int x, int y) const
//{
//	return charMap[y][x];
//}

void World::SetCharFromXandY(const int& x, const int& y, const char& toChar) 
{
	charMap[y][x] = toChar;
}

void World::PrintCharFromXandY(const int& x, const int& y)const
{

	Scene::GotoXY(x + (1 * x), y, topLeftPos);
	cout << charMap[y][x] << " ";
}

const Vector2 World::GetTopLeft() const
{
	return topLeftPos;
}

void World::Update(GameObject** objects, int objectsCount)
{
	Vector2* pos;
	for (int i = 0; i < objectsCount; i++)
	{
		Vector2::Clamp(*objects[i]->GetPosition(), Vector2(9, 9), Vector2(0, 0));
		if (!objects[i]->GetActive())
		{
			continue;
		}
		pos = objects[i]->GetPosition();
		charMap[objects[i]->GetPrevPosition().GetY()][objects[i]->GetPrevPosition().GetX()] = '.';

		if (charMap[pos->GetY()][pos->GetX()] == '.')
		{
			charMap[pos->GetY()][pos->GetX()] = objects[i]->GetObjectChar();
		}
		else 
		{
			Vector2 collidedPos = Vector2(pos->GetX(), pos->GetY());
			*pos = objects[i]->GetPrevPosition();
			GameObject* collidedObj = ObjectManager::getObjectManager()->GetObjectAtPosition(collidedPos);
			if (collidedObj)
			{
				collidedObj->Collided(objects[i]);
				objects[i]->Collided(collidedObj);
			}
		}

		if (*pos == objects[i]->GetPrevPosition())
			charMap[pos->GetY()][pos->GetX()] = objects[i]->GetObjectChar();
	}

}

void World::Render(GameObject** objects, int objectsCount)
{
	Vector2* pos;

	for (int i = 0; i < objectsCount; i++)
	{
		pos = objects[i]->GetPosition();
		if (*pos != objects[i]->GetPrevPosition())
		{

			Scene::GotoXY(objects[i]->GetPrevPosition().GetX() + (1* objects[i]->GetPrevPosition().GetX()), objects[i]->GetPrevPosition().GetY(), topLeftPos);
			cout << charMap[objects[i]->GetPrevPosition().GetY()][objects[i]->GetPrevPosition().GetX()] << " ";

			Scene::GotoXY(pos->GetX()+ (1* pos->GetX()), pos->GetY(), topLeftPos);
			cout << charMap[pos->GetY()][pos->GetX()] << " ";
		}
		else 
		{
			Scene::GotoXY(pos->GetX() + (1 * pos->GetX()), pos->GetY(), topLeftPos);
			cout << charMap[pos->GetY()][pos->GetX()] << " ";
		}

	}
}

void World::Render()
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			Scene::GotoXY(x + (1*x), y, topLeftPos);
			cout << charMap[y][x] << " ";
		}
	}
}
