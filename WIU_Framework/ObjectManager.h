#pragma once
#include "GameObject.h"
/// <summary>
/// Handles All Objects in the background
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
	void AddGameObjects(void);
	void RemoveGameObjects(void);

public:
	ObjectManager(void);
	void Start(void);

	GameObject** GetObjects(void);
	int GetObjectsCount(void) const;


	GameObject* GetObjectAtPosition(const Vector2& atPos) const;
	void InstantiateObject(GameObject* obj);
	void DestroyObject(GameObject* obj);


	void UpdateObjects(void);
	static ObjectManager* getObjectManager();
};

