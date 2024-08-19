#pragma once
#include "Scene.h"
class KitchenScene :
    public Scene
{

public:
    KitchenScene(void);
    void Start() override;
    void Update() override;

};

