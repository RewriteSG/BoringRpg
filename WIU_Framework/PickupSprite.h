#pragma once
#include "Sprite.h"
class PickupSprite :
    public Sprite
{
    void Render(int x, int y, Vector2 topLeft)override;
};

