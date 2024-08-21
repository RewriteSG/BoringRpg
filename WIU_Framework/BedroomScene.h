#pragma once
#include "Scene.h"
#include "Robber.h"
class BedroomScene :
    public Scene
{
public:
    BedroomScene();
    void Start() override;
    void Update() override;

    //Robber draw;
};


