#include "Endings.h"
#include "SceneManager.h"
#include "Furniture.h"
#include "UI.h"
#include "conio.h"

Endings::Endings()
{
	name = SceneManager::GetSceneName(SceneManager::ENDINGS);
}
void Endings::Start()
{
	Scene::Start();
}


void Endings::Update()
{
	Scene::Update();
}
