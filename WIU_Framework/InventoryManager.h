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
	PickupableItem::TypeOfPickup* getItemInInventory(string item);
public:
	InventoryManager();
	bool PickupItem(PickupableItem::TypeOfPickup typeofPickup);
	string** GetItems();
	bool InventoryHasItems(string item1);
	bool InventoryHasItems(string item1, string item2);
	bool InventoryHasItems(string item1, string item2, string item3);
	void DropItem(string dropItem);
	void UseItem(string useItem);
};

