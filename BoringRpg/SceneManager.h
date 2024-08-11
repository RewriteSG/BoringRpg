#pragma once
using namespace std;
#include "Scene.h"
class SceneManager
{
	static Scene* nextScene;
public:
	static Scene* CurrentScene;
	SceneManager();
	static void Start();
	static void Update();
	static void LoadScene(Scene* toScene);
	static void Exit();
};

