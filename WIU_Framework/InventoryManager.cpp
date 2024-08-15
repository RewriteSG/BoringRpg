#include "InventoryManager.h"

PickupableItem::TypeOfPickup* InventoryManager::getItemInInventory(PickupableItem::TypeOfPickup item)
{

	for (int i = 0; i < inventoryCurrentCapacity; i++)
	{
		if (*Items[i] == item)
			return Items[i];
	}
	return nullptr;
}

InventoryManager::InventoryManager()
{
	Items = nullptr;
	inventoryCurrentCapacity = 3;
	inventoryMaxCapacity = 0;
}

bool InventoryManager::PickupItem(PickupableItem::TypeOfPickup typeofPickup)
{
	if (inventoryCurrentCapacity >= inventoryCurrentCapacity)
		return false;
	PickupableItem::TypeOfPickup* newItem = new PickupableItem::TypeOfPickup; 
	*newItem = typeofPickup;
	Items = ArrayAdd(Items, newItem, inventoryCurrentCapacity);
	return true;
}

PickupableItem::TypeOfPickup** InventoryManager::GetItems()
{
	return Items;
}

bool InventoryManager::InventoryHasItems(PickupableItem::TypeOfPickup item1)
{
	bool hasItem1 = false; 
	for (int i = 0; i < inventoryCurrentCapacity; i++)
	{
		if (*Items[i] == item1)
			hasItem1 = true;
	}
	return hasItem1;
}

bool InventoryManager::InventoryHasItems(PickupableItem::TypeOfPickup item1, PickupableItem::TypeOfPickup item2)
{
	bool hasItem1 = false , hasItem2 = false; 

	for (int i = 0; i < inventoryCurrentCapacity; i++)
	{
		if (*Items[i] == item1)
			hasItem1 = true;
		if (*Items[i] == item2)
			hasItem2 = true;
	}
	return hasItem1 && hasItem2;
}

bool InventoryManager::InventoryHasItems(PickupableItem::TypeOfPickup item1, PickupableItem::TypeOfPickup item2, PickupableItem::TypeOfPickup item3)
{
	bool hasItem1 = false, hasItem2 = false, hasItem3 = false; 


	for (int i = 0; i < inventoryCurrentCapacity; i++)
	{
		if (*Items[i] == item1)
			hasItem1 = true;
		if (*Items[i] == item2)
			hasItem2 = true;
		if (*Items[i] == item3)
			hasItem3 = true;
	}
	return hasItem1 && hasItem2 && hasItem3;
}

void InventoryManager::DropItem(PickupableItem::TypeOfPickup dropItem)
{
	PickupableItem::TypeOfPickup* item = getItemInInventory(dropItem);
	Items = ArrayRemove(Items, item, inventoryCurrentCapacity);

}

void InventoryManager::UseItem(PickupableItem::TypeOfPickup useItem)
{
	PickupableItem::TypeOfPickup* item = getItemInInventory(useItem);
	Items = ArrayRemove(Items, item, inventoryCurrentCapacity);

}

