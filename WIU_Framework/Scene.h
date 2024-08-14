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

	enum TypeColor
	{
		Red,
		Green, 
		Blue,
		Purple,
		Yellow,
		Black,
		White,
		Default
	};

	static void ChangeColor(TypeColor color);
	static void ChangeColor(TypeColor color, bool toCharColors);
	static void LowerString(string& _string);
};

