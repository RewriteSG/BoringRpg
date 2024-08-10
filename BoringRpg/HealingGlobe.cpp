#include "HealingGlobe.h"

HealingGlobe::HealingGlobe()
{
	Heal = 0;
	Start();
}

HealingGlobe::HealingGlobe(Vector2 toPos)
{
	Heal = 0;
	*GetPosition() = toPos;
	Start();
}

HealingGlobe::HealingGlobe(Vector2 toPos, int SetId)
{
	Heal = 0;
	SetID(SetId);
	*GetPosition() = toPos;
	Start();
}

void HealingGlobe::Start()
{
	Heal = 20;
	SetObjectChar('H');
}

int HealingGlobe::GetHeal() const
{
	return Heal;
}
