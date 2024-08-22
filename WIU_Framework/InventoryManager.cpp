#include "InventoryManager.h"
#include "UI.h"
#include "MyFunctions.cpp"
#include "GameManager.h"
#include "Scene.h"
#include "Application.h"
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
	hasChangedCapacity = true;
}

bool InventoryManager::PickupItem(std::string typeofPickup)
{
	//if (inventoryCurrentCapacity >= inventoryCurrentCapacity)
	//	return false;
	std::string * newItem = new std::string ; 
	*newItem = Scene::tolowerString(typeofPickup);

	Items = ArrayAdd(Items, newItem, inventoryCurrentCapacity);
	hasChangedCapacity = true;

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

void InventoryManager::DisplayItems() 
{

	UI gameUI(Vector2(150, 12), 0, 45);
	if (hasChangedCapacity) {

		hasChangedCapacity = false;
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
	gameUI.CreateText("[ Enter <item name> to see tooltip ]", Vector2(2,2));
	}

	for (int i = 0; i < inventoryCurrentCapacity; i++)
	{
		//Scene::ChangeColor(Scene::Yellow);
		GameManager::getGM()->gameUI->CreateText(*Items[i], Vector2(18, 6 + i), 14-7);
	}
}

void InventoryManager::DisplayItems(bool)
{
	UI gameUI(Vector2(150, 12), 0, 45);
	//hasChangedCapacity = false;
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
	gameUI.CreateText("[ Enter <item name> to see tooltip ]", Vector2(2, 2));
	for (int i = 0; i < inventoryCurrentCapacity; i++)
	{
		//Scene::ChangeColor(Scene::Yellow);
		GameManager::getGM()->gameUI->CreateText(*Items[i], Vector2(18, 6 + i), 14 - 7);
	}
}

bool InventoryManager::InventoryHasItems(std::string item1) const
{
	if (item1 == "key")
	{
		UI ui(Vector2(Application::numberOfColumns / 2 - 171 / 2, 35), 0, 166);
		ui.PrintDialogue(Vector2(3, 2), "Make sure to enter the key with its name as shown in inventory. ");

	}
	bool hasItem1 = false; 
	for (int i = 0; i < inventoryCurrentCapacity; i++)
	{
		if (*Items[i] == item1)
			hasItem1 = true;
	}
	return hasItem1;
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
	useItem = Scene::tolowerString(useItem);
	std::string * item = getItemInInventory(useItem);
	Items = ArrayRemove(Items, item, inventoryCurrentCapacity);

	if (prevCapacityCount != inventoryCurrentCapacity) {

		std::string clearText = "";
		for (int j = 0; j < 45; j++)
		{
			clearText += ' ';
		}
		for (int i = 0; i <= 5 + prevCapacityCount; i++)
		{
			gameUI.CreateText(clearText, Vector2(-5, 2 + i));
		}
		hasChangedCapacity = true;
		gameUI.CreateBox(Vector2(-5, 2), "Inventory:", 5 + (inventoryCurrentCapacity + 1));
		gameUI.CreateText("[ Enter <item name> to see tooltip ]", Vector2(2, 2));

		for (int i = 0; i < inventoryCurrentCapacity; i++)
		{
			//Scene::ChangeColor(Scene::Yellow);
			GameManager::getGM()->gameUI->CreateText(*Items[i], Vector2(18, 6 + i), 14 - 7);
		}
	}
}

