#pragma once
#include "World.h"
#include "Vector2.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include <iostream>
#include "UI.h"
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
	
	virtual void Render();
	virtual void Exit();
	virtual bool GetContinuePgrm() const;

	static void GotoXY(int x, int y, Vector2 WorldTopLeft);
	static void GotoXY(int x, int y);

	enum TypeColor
	{
		Red,
		Green, 
		Blue,
		Purple,
		Yellow,
		Black,
		White,
		BG_COLOR
	};

	static void ChangeColor(const TypeColor color);
	static void ChangeColor(const int color);
	static void LowerString(string& _string);
};

