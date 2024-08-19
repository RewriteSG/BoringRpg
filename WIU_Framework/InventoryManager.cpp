#include "InventoryManager.h"
#include "UI.h"
#include "MyFunctions.cpp"
#include "GameManager.h"
#include "Scene.h"
using namespace myFunctions;
std::string * InventoryManager::getItemInInventory(std::string item)
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
	inventoryCurrentCapacity = 0;
	inventoryMaxCapacity = 0;
}

bool InventoryManager::PickupItem(std::string typeofPickup)
{
	//if (inventoryCurrentCapacity >= inventoryCurrentCapacity)
	//	return false;
	std::string * newItem = new std::string ; 
	*newItem = Scene::tolowerString(typeofPickup);

	Items = ArrayAdd(Items, newItem, inventoryCurrentCapacity);
	return true;
}

std::string ** InventoryManager::GetItems()
{
	return Items;
}

void InventoryManager::DisplayItems() const
{

	for (int i = 0; i < inventoryCurrentCapacity; i++)
	{
		GameManager::getGM()->gameUI->CreateText(*Items[i], Vector2(18, 4 + i));
	}
}

bool InventoryManager::InventoryHasItems(std::string item1) const
{
	bool hasItem1 = false; 
	for (int i = 0; i < inventoryCurrentCapacity; i++)
	{
		if (*Items[i] == item1)
			hasItem1 = true;
	}
	return hasItem1;
}

bool InventoryManager::InventoryHasItems(std::string item1, std::string item2) const
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

bool InventoryManager::InventoryHasItems(std::string item1, std::string item2, std::string item3) const
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

void InventoryManager::DropItem(std::string dropItem)
{
	std::string * item = getItemInInventory(dropItem);
	Items = ArrayRemove(Items, item, inventoryCurrentCapacity);

}

void InventoryManager::UseItem(std::string useItem)
{
	std::string * item = getItemInInventory(useItem);
	Items = ArrayRemove(Items, item, inventoryCurrentCapacity);

}

