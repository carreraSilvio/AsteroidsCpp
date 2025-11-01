#include "BrightEntity.h"

unsigned int BrightEntity::NEXT_ID = 0;

BrightEntity::BrightEntity()
{
	active = true;
	id = NEXT_ID++;
	position = { 0,0 };
}

/*
void BrightEntity::update(float dt)
{
	if (!active)
	{
		return;
	}
	//update components
}

void BrightEntity::draw(sf::RenderWindow& window)
{
	//
	if (!active)
	{
		return;
	}

	window.draw(shape);
}
*/
