#pragma once
#include "Vector2.h"
#include "GameObject.h"
/// <summary>
/// A World Class that handles the render and the keeping the objects bound in the world, also handling the collisions
/// </summary>
class World
{
	static World* worldInstance;
	Vector2 topLeftPos;
	Vector2 botRightPos;
	char** charMap;
	int width, height;

public:
	static World* GetWorldInstance();
	World();
	World(Vector2 topLeft);
	World(Vector2 topLeft, int toWidth, int toHeight);
	void Start();
	//const char GetCharFromXandY(int x, int y)const;
	void SetCharFromXandY(const int& x, const int& y, const char& toChar);
	void PrintCharFromXandY(const int& x,const int& y)const;
	const Vector2 GetTopLeft() const;
	void Update(GameObject** objects, int objectsCount);
	void Render(GameObject** objects, int objectsCount);
	void Render();
};

