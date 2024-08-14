#pragma once
#include "iostream"
#include "PickupableItem.h"
#include "MyFunctions.cpp"
using namespace myFunctions;
using namespace std;
class InventoryManager
{
	int inventoryMaxCapacity;
	int inventoryCurrentCapacity;
	PickupableItem::TypeOfPickup** Items;
	PickupableItem::TypeOfPickup* getItemInInventory(PickupableItem::TypeOfPickup item);
public:
	InventoryManager();
	bool PickupItem(PickupableItem::TypeOfPickup typeofPickup);
	PickupableItem::TypeOfPickup** GetItems();
	bool InventoryHasItems(PickupableItem::TypeOfPickup item1);
	bool InventoryHasItems(PickupableItem::TypeOfPickup item1, PickupableItem::TypeOfPickup item2);
	bool InventoryHasItems(PickupableItem::TypeOfPickup item1, PickupableItem::TypeOfPickup item2, PickupableItem::TypeOfPickup item3);
	void DropItem(PickupableItem::TypeOfPickup dropItem);
	void UseItem(PickupableItem::TypeOfPickup useItem);
};

