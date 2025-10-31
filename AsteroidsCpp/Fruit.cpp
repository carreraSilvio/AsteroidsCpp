#include "Fruit.h"
#include "GameConstants.h"
#include "BrightLib/BrightRandom.h"

Fruit::Fruit(float x, float y)
{
	startX = x;
	startY = y;
	position = {x, y};
	radius = 10.0f;

	active = true;

	shape.setRadius(radius);
	shape.setFillColor(sf::Color(255, 0, 0));
	shape.setPosition(sf::Vector2(x, y));
}

void Fruit::resetPosition()
{
	active = true;

	position.x = startX;
	position.y = startY;
	shape.setPosition(position);
}

void Fruit::update(float deltaTime)
{
	if (!active)
	{
		return;
	}

	shape.setPosition(position);
}

void Fruit::draw(sf::RenderWindow& window)
{
	if (!active)
	{
		return;
	}

	window.draw(shape);
}

void Fruit::setPosition(float x, float y)
{
	position = { x,y };
	setPosition(position);
}
void Fruit::setPosition(sf::Vector2f position)
{
	this->position = position;
	shape.setPosition(position);
}
