#pragma once
#include "Sprite.h"
class SoapSprite :
    public Sprite
{
public:
    void Render(int x, int y, Vector2 topLeft) override;
};

