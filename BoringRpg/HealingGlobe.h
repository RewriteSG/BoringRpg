#pragma once
#include "Items.h"
class HealingGlobe :
    public Item
{
    int Heal;
public:
    HealingGlobe();
    HealingGlobe(Vector2 toPos);
    HealingGlobe(Vector2 toPos, int SetId);
    virtual void Start()override;
    int GetHeal() const;
};

