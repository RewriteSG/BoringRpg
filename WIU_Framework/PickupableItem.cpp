#include "PickupableItem.h"

PickupableItem::PickupableItem(TypeOfPickup pickup, Vector2 toPos)
{
	typeOfPickup = pickup;
	*GetPosition() = toPos;
}

void PickupableItem::Start()
{
	
}

void PickupableItem::Collided(GameObject* collided)
{

}
