#include "Soap.h"
#include "SoapSprite.h"
Soap::Soap(Vector2 toPos)
{
	position = toPos;
	SetSprite(new SoapSprite());
	isTrigger = true;
}
