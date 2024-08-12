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
	virtual void Update();
	virtual void Collided(GameObject* collision);
	virtual void OnDestroyed();
	bool GetActive() const;
	void SetActive(bool);
};

