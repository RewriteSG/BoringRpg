#pragma once
using namespace std;
#include "Scene.h"
class SceneManager
{
	Scene* nextScene;
public:
	Scene* CurrentScene;
	SceneManager();
	void Start();
	void Update();
	void LoadScene(Scene* toScene);
	void Exit();
};

