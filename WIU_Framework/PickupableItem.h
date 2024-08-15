#pragma once
#include "Items.h"
class PickupableItem :
    public Item
{
public:
	enum TypeOfPickup
	{
		KeysToCloset,
		KeysToToiletCabinet,
		Soap,
		Planks,
		Nails,
		Hammer,
		Boxes,
		MetalPan,
		Knife,
		Phone,
		DuctTape
	};
private:
	TypeOfPickup typeOfPickup;
public:
    PickupableItem(TypeOfPickup pickup , Vector2 toPos);
	void Start() override;	
	void Collided(GameObject* collided) override;
};

