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

int InventoryManager::GetItemsCount()
{
	return inventoryCurrentCapacity;
}

void InventoryManager::DisplayItems() const
{

	UI gameUI(Vector2(150, 12), 0, 45);
	std::string clearText = "";
	for (int j = 0; j < 45; j++)
	{
		clearText += ' ';
	}
	for (int i = 0; i <= 5 + inventoryCurrentCapacity; i++)
	{
		gameUI.CreateText(clearText, Vector2(-5, 2 + i));
	}
	gameUI.CreateBox(Vector2(-5, 2), "Inventory:", 5 + (inventoryCurrentCapacity + 1));
	for (int i = 0; i < inventoryCurrentCapacity; i++)
	{
		GameManager::getGM()->gameUI->CreateText(*Items[i], Vector2(18, 6 + i));
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
	UI gameUI(Vector2(150, 12), 0, 45);
	int prevCapacityCount = inventoryCurrentCapacity;

	std::string * item = getItemInInventory(useItem);
	Items = ArrayRemove(Items, item, inventoryCurrentCapacity);
	if (prevCapacityCount != inventoryCurrentCapacity)
		gameUI.CreateBox(Vector2(-5, 2), "Inventory:", 5 + (inventoryCurrentCapacity + 1));
}

