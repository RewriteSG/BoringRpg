#include "Wall.h"
#include "WallSprite.h"
Wall::Wall()
{
	SetSprite(new WallSprite());
}

Wall::Wall(Vector2 toPos)
{
	SetSprite(new WallSprite());
	GetPosition()->SetXandY(toPos.GetX(), toPos.GetY());
}
