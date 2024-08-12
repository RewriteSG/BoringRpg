#include "Items.h"

Item::Item()
{
	id = 0;
	Start();
}


int Item::GetID() const
{
	return id;
}

void Item::SetID(int toId)
{
	id = toId;
}
