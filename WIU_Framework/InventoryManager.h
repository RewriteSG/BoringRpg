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
	int GetItemsCount();

	void DisplayItems() const;
	bool InventoryHasItems(std::string item1) const;
	bool InventoryHasItems(std::string item1, std::string item2) const;
	bool InventoryHasItems(std::string item1, std::string item2, std::string item3) const;
	void DropItem(std::string dropItem);
	void UseItem(std::string useItem);
};

