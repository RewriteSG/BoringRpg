#pragma once
#include "Scene.h"
class ToiletScene :
    public Scene
{
public:
    ToiletScene(void);
    void Start() override;
    void Update() override;
};


