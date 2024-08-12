#pragma once
#include "World.h"
#include "Vector2.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include <iostream>
class Scene
{
public:
	World world;
	ObjectManager objectManager;
	GameManager gm; 
	bool ContinuePgrm;
	Scene();
	virtual void Start();
	virtual void Update();

	void Render();
	void Exit();
	bool GetContinuePgrm() const;
	static void GotoXY(int x, int y, Vector2 WorldTopLeft);
	static void GotoXY(int x, int y);

	static void LowerString(string& _string);
};

