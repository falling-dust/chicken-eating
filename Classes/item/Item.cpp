#include "Item.h"

Sprite* Item::getSprite()
{
	return this->mySprite;
}

void Item::bindSprite(Sprite* sprite)
{
	this->mySprite = sprite;
	this->addChild(mySprite);
}

void Item::setState(bool InHand)
{
	MyInHand = InHand;
}

bool Item::getState()
{
	return MyInHand;
}

void Item::flipSprite(bool isFlip)
{
	mySprite->setFlippedX(isFlip);
}
