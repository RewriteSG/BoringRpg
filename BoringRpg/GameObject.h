#pragma once
#include "Vector2.h"
class GameObject
{
	char symbol;
	Vector2 position;
	Vector2 prevPosition;
	bool IsActive;
public:
	GameObject();
	GameObject(Vector2 toPos);
	Vector2* GetPosition();
	char GetObjectChar() const;
	void SetObjectChar(char toChar);
	const Vector2 GetPrevPosition() const;
	void UpdatePosition();
	virtual void Start();
	//virtual void Start();
	virtual void Update() = 0;
	virtual void Collided(GameObject* collision) = 0;
	virtual void OnDestroyed() = 0;
	bool GetActive() const;
	void SetActive(bool);
};

