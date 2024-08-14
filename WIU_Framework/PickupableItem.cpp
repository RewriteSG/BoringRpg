#include "PickupableItem.h"
#include "PickupSprite.h"
PickupableItem::PickupableItem(TypeOfPickup pickup, Vector2 toPos)
{
	typeOfPickup = pickup;
	*GetPosition() = toPos;
	SetSprite(new PickupSprite());
}

void PickupableItem::Start()
{
	
}

void PickupableItem::Collided(GameObject* collided)
{

}
