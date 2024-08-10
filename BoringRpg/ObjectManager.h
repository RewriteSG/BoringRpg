#pragma once
#include "GameObject.h"
/// <summary>
/// Handles
/// </summary>
class ObjectManager
{

	GameObject** gameObjects;
	GameObject** gameObjectsToAdd;
	GameObject** gameObjectsToRemove;
	static ObjectManager* objectManagerInstance;



	int gameObjectsCount, gameObjectsToAddCount, gameObjectsToRemoveCount;
	GameObject** AddGameObject(GameObject** Array, GameObject* toAdd, int& count);
	GameObject** RemoveGameObject(GameObject** Array, GameObject* toRemove, int& count);
	GameObject** RemoveGameObject(GameObject** Array, GameObject* toRemove, int& count, bool DeleteObj);
	int GameObjectIndex(GameObject** Array, GameObject* indexOf, const int& count)const;
	bool GameObjectsArrayContains(GameObject** Array, GameObject* obj, const int& count)const;
	void AddGameObjects();
	void RemoveGameObjects();

public:
	ObjectManager();
	void Start();
	GameObject** GetObjects();
	int GetObjectsCount() const;
	GameObject* GetObjectAtPosition(const Vector2& atPos) const;
	void InstantiateObject(GameObject* obj);
	void DestroyObject(GameObject* obj);
	void UpdateObjects();
	void UpdateObjectsPosition();
	static ObjectManager* getObjectManager();
};

