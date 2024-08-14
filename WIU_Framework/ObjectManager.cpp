#include "ObjectManager.h"
#include "World.h"
#include "Windows.h"
ObjectManager* ObjectManager::objectManagerInstance = nullptr;

ObjectManager::ObjectManager(void)
{
	objectManagerInstance = this;
	gameObjects = nullptr;
	gameObjectsToAdd = nullptr;
	gameObjectsCount = 0;
	gameObjectsToAddCount = 0;
	gameObjectsToRemove = nullptr;
	gameObjectsToRemoveCount = 0;
}

void ObjectManager::Start(void)
{
	objectManagerInstance = this;
	gameObjects = nullptr;
	gameObjectsToAdd = nullptr;
	gameObjectsCount = 0;
	gameObjectsToAddCount = 0;
	gameObjectsToRemove = nullptr;
	gameObjectsToRemoveCount = 0;
}

GameObject** ObjectManager::GetObjects()
{
	return gameObjects;
}

int ObjectManager::GetObjectsCount() const
{
	return gameObjectsCount;
}

GameObject* ObjectManager::GetObjectAtPosition(const Vector2& atPos) const
{
	for (int i = 0; i < gameObjectsCount; i++)
	{
		if (*gameObjects[i]->GetPosition() == atPos)
			return gameObjects[i];
	}
	return nullptr;
}

void ObjectManager::InstantiateObject(GameObject* obj)
{
	gameObjectsToAdd = AddGameObject(gameObjectsToAdd, obj, gameObjectsToAddCount);
}

void ObjectManager::DestroyObject(GameObject* obj)
{
	if (!GameObjectsArrayContains(gameObjectsToRemove, obj, gameObjectsToRemoveCount))
		gameObjectsToRemove = AddGameObject(gameObjectsToRemove, obj, gameObjectsToRemoveCount);

}

void ObjectManager::UpdateObjects()
{
	AddGameObjects();
	RemoveGameObjects();

	for (int i = 0; i < gameObjectsCount; i++)
	{
		gameObjects[i]->UpdatePosition();
		gameObjects[i]->Update();
	}

	AddGameObjects();
	RemoveGameObjects();
}

void ObjectManager::UpdatePositions()
{
	for (int i = 0; i < gameObjectsCount; i++)
	{
		gameObjects[i]->UpdatePosition();
		//gameObjects[i]->Update();
	}
}

GameObject** ObjectManager::AddGameObject(GameObject** Array, GameObject* toAdd, int& ArraySize)
{

	GameObject** temp = new GameObject * [ArraySize + 1];

	if (Array)
	{
		for (int i = 0; i < ArraySize; i++)
		{
			temp[i] = Array[i];

		}
		delete[] Array;

	}

	temp[ArraySize] = toAdd;

	Array = new GameObject * [ArraySize + 1];
	for (int i = 0; i < ArraySize + 1; i++)
	{
		Array[i] = temp[i];
	}
	ArraySize++;
	delete[] temp;
	return Array;
}

GameObject** ObjectManager::RemoveGameObject(GameObject** Array, GameObject* toRemove, int& ArraySize)
{
	int indexToRemove = GameObjectIndex(Array, toRemove, ArraySize);
	if (indexToRemove == -1)
		return Array;

	GameObject** temp = new GameObject * [ArraySize - 1];
	int loopIndex = 0;

	if (Array)
	{
		for (int i = 0; i < ArraySize; i++)
		{
			if (Array[i] == toRemove)
			{
				Array[i] = nullptr;
				continue;
			}
			temp[loopIndex] = Array[i];
			loopIndex++;
		}
		delete[] Array;
	}

	Array = new GameObject * [ArraySize - 1];
	for (int i = 0; i < ArraySize - 1; i++)
	{
		Array[i] = temp[i];
	}
	ArraySize--;
	delete[] temp;
	return Array;
}

GameObject** ObjectManager::RemoveGameObject(GameObject** Array, GameObject* toRemove, int& ArraySize, bool DeleteObject)
{
	int indexToRemove = GameObjectIndex(Array, toRemove, ArraySize);
	if (indexToRemove == -1)
		return Array;

	GameObject** temp = new GameObject * [ArraySize - 1];
	int loopIndex = 0;

	if (Array)
	{
		for (int i = 0; i < ArraySize; i++)
		{
			if (Array[i] == toRemove)
			{

				if (Array[i])
					delete Array[i];

				Array[i] = nullptr;
				continue;
			}
			temp[loopIndex] = Array[i];
			loopIndex++;
		}
		delete[] Array;
	}

	Array = new GameObject * [ArraySize - 1];
	for (int i = 0; i < ArraySize - 1; i++)
	{
		Array[i] = temp[i];
	}
	ArraySize--;
	delete[] temp;
	return Array;
}

int ObjectManager::GameObjectIndex(GameObject** Array, GameObject* indexOf, const int& count) const
{
	int toreturn = -1;
	for (int i = 0; i < count; i++)
	{
		if (Array[i] == indexOf) 
		{
			return i;
		}
	}
	return toreturn;
}

bool ObjectManager::GameObjectsArrayContains(GameObject** Array, GameObject* obj, const int& count) const
{
	for (int i = 0; i < count; i++)
	{
		if (Array[i] == obj)
		{
			return true;
		}
	}
	return false;
}

void ObjectManager::AddGameObjects()
{
	if (gameObjectsToAdd)
	{
		int toAdd = gameObjectsToAddCount;
		Vector2* pos;
		for (int i = 0; i < toAdd; i++)
		{
			pos = gameObjectsToAdd[i]->GetPosition();
			Vector2::Clamp(pos, Vector2(World::GetWorldInstance()->width-1, World::GetWorldInstance()->height-1), Vector2(0, 0));
			//gameObjectsToAdd[i]->Start();
			World::GetWorldInstance()->SetCharFromXandY(pos->GetX(), pos->GetY(), gameObjectsToAdd[i]->GetObjectChar());

			gameObjects = AddGameObject(gameObjects, gameObjectsToAdd[i], gameObjectsCount);
		}
		delete[] gameObjectsToAdd;
		gameObjectsToAddCount = 0;
		gameObjectsToAdd = nullptr;
	}
}

void ObjectManager::RemoveGameObjects()
{
	if (gameObjectsToRemove)
	{
		int toRemove = gameObjectsToRemoveCount;
		Vector2* pos;
		for (int i = 0; i < toRemove; i++)
		{
			pos = gameObjectsToRemove[i]->GetPosition();
			gameObjectsToRemove[i]->OnDestroyed();
			World::GetWorldInstance()->SetCharFromXandY(pos->GetX(), pos->GetY(), '.');
			World::GetWorldInstance()->PrintCharFromXandY(pos->GetX(), pos->GetY());
			gameObjects = RemoveGameObject(gameObjects, gameObjectsToRemove[i], gameObjectsCount);
		}
		delete[] gameObjectsToRemove;
		gameObjectsToRemoveCount = 0;
		gameObjectsToRemove = nullptr;
	}
}

ObjectManager* ObjectManager::getObjectManager()
{
	return objectManagerInstance;
}


