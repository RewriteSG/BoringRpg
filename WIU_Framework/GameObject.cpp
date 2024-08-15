#include "GameObject.h"
#include "ObjectManager.h"
#include "World.h"
GameObject::GameObject(void)
{
	name = "";
	symbol = '*';
	ObjectManager::getObjectManager()->InstantiateObject(this);
	IsActive = true;
	isRenderSprite = true;
	sprite = new Sprite();
	Start();
}

GameObject::GameObject(Vector2 toPos)
{
	name = "";
	symbol = '*';
	ObjectManager::getObjectManager()->InstantiateObject(this);
	position = toPos;
	IsActive = true;
	sprite = new Sprite();
	isRenderSprite = true;
	Start();
}

Vector2* GameObject::GetPosition(void)
{
	return &position;
}

Vector2 GameObject::GetPosition(bool) const
{
	return position;
}

char GameObject::GetObjectChar(void) const
{
	return symbol;
}

void GameObject::SetObjectChar(char toChar)
{
	symbol = toChar;
}

const Vector2 GameObject::GetPrevPosition(void) const
{
	return prevPosition;
}


void GameObject::UpdatePosition()
{
	prevPosition = position;
}


void GameObject::Start(void)
{
	IsActive = true;
}

void GameObject::Update(void) {}
void GameObject::Collided(GameObject* collision) {}
void GameObject::OnDestroyed(void) {}

void GameObject::SetSprite(Sprite* _sprite)
{
	if (!_sprite)
		return;
	delete sprite;
	sprite = _sprite;

}

Sprite* GameObject::GetSprite(void)
{
	return sprite;
}

bool GameObject::IsRenderingSprite()
{
	return isRenderSprite;
}

void GameObject::SetRenderSprite(bool toBool)
{
	isRenderSprite = toBool;
}

bool GameObject::GetActive(void) const
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

std::string GameObject::GetName(void) const
{
	return name;
}
