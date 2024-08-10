#include "GameObject.h"
#include "ObjectManager.h"
#include "World.h"
GameObject::GameObject()
{
	symbol = '*';
	ObjectManager::getObjectManager()->InstantiateObject(this);
	IsActive = true;
	Start();
}

GameObject::GameObject(Vector2 toPos)
{
	symbol = ' ';
	position = toPos;
	IsActive = true;
}

Vector2* GameObject::GetPosition()
{
	return &position;
}

char GameObject::GetObjectChar() const
{
	return symbol;
}

void GameObject::SetObjectChar(char toChar)
{
	symbol = toChar;
}

const Vector2 GameObject::GetPrevPosition() const
{
	return prevPosition;
}


void GameObject::UpdatePosition()
{
	prevPosition = position;
}


void GameObject::Start()
{
	IsActive = true;
}

bool GameObject::GetActive() const
{
	return IsActive;
}

void GameObject::SetActive(bool setActive)
{
	IsActive = setActive;
	if (!IsActive) 
	{
		Vector2* pos = GetPosition();
		World::GetWorldInstance()->SetCharFromXandY(pos->GetX(),pos->GetY(), '.');
		Vector2 prevPos = GetPrevPosition();
		World::GetWorldInstance()->SetCharFromXandY(prevPos.GetX(), prevPos.GetY(), '.');

	}
}
