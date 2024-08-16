#pragma once
#include "World.h"
#include "Vector2.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include <iostream>
class Scene
{
protected:
	std::string name;
	World world;
	ObjectManager objectManager;
public:
	static GameManager gm; 
	bool ContinuePgrm;
	Scene();
	virtual void Start();
	virtual void Update();
	void UpdateGameObjectsPos();
	virtual void Render();
	virtual void Exit();
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
		Default,
		BG_COLOR
	};

	static void ChangeColor(TypeColor color);
	static void ChangeColor(TypeColor color, bool toCharColors);
	static void ChangeColor(int);
	static void LowerString(string& _string);

	std::string getName(void) const;
};

