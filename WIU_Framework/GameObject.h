#pragma once
#include "Vector2.h"
#include "Sprite.h"
#include <iostream>
class GameObject
{
protected:
	std::string name;
	char symbol;
	Vector2 position;
	Vector2 prevPosition;
	Sprite* sprite;
	bool IsActive;
	bool isRenderSprite;

public:
	GameObject(void);
	GameObject(Vector2 toPos);

	Vector2* GetPosition(void);
	Vector2 GetPosition(bool)const;
	const Vector2 GetPrevPosition(void) const;

	void SetObjectChar(char toChar);
	char GetObjectChar(void) const;

	void UpdatePosition(void);

	virtual void Start(void);
	virtual void Update(void);
	virtual void Collided(GameObject* collision);
	virtual void OnDestroyed(void);

	void SetSprite(Sprite* sprite);
	Sprite* GetSprite(void);

	bool IsRenderingSprite();
	void SetRenderSprite(bool);
	bool GetActive(void) const;
	void SetActive(bool setActive);

	std::string GetName(void) const;
};

