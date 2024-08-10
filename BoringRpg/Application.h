#pragma once
using namespace std;
#include "Scene.h"

class Application
{
public:
	Scene scene;
	Application();
	void Start();
	void Update();
	void Exit();
};

