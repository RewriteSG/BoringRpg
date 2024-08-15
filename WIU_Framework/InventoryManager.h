#pragma once
#include <iostream>
#include "PickupableItem.h"
using namespace std;
class InventoryManager
{
	int inventoryMaxCapacity;
	int inventoryCurrentCapacity;
	std::string** Items;
	std::string* getItemInInventory(std::string item);
public:
	InventoryManager();
	bool PickupItem(std::string typeofPickup);
	std::string** GetItems();

	void DisplayItems();
	bool InventoryHasItems(std::string item1);
	bool InventoryHasItems(std::string item1, std::string item2);
	bool InventoryHasItems(std::string item1, std::string item2, std::string item3);
	void DropItem(std::string dropItem);
	void UseItem(std::string useItem);
};

