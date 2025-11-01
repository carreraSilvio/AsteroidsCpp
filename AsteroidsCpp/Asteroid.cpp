#include "Asteroid.h"
#include "GameConstants.h"
#include "BrightLib/BrightRandom.h"

Asteroid::Asteroid(float x, float y) 
	: BrightEntity(),
	speed(100.0f),
	direction(1.0f,0.5f),
	radius(50.0f)
{
	position = {x, y};

	shape.setRadius(radius);
	//shape.setFillColor(sf::Color::Transparent);
	shape.setFillColor(sf::Color(129,128,128));
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1.0f);
	shape.setPosition(sf::Vector2(x, y));
}

void Asteroid::resetPosition()
{
	shape.setPosition(position);
}

void Asteroid::update(float dt)
{
	if (!active)
	{
		return;
	}

	position += speed * direction * dt;

	shape.setPosition(position);
}

void Asteroid::draw(sf::RenderWindow& window)
{
	if (!active)
	{
		return;
	}

	window.draw(shape);
}

void Asteroid::setPosition(float x, float y)
{
	position = { x,y };
	setPosition(position);
}
void Asteroid::setPosition(sf::Vector2f position)
{
	this->position = position;
	shape.setPosition(position);
}