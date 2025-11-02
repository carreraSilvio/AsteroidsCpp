#include "Asteroid.h"
#include "GameConstants.h"
#include "BrightLib/BrightRandom.h"

Asteroid::Asteroid(float x, float y) 
	: BrightEntity(),
	size(SMALL_SIZE),
	speed(LOW_SPEED),
	direction(0.0f,0.0f),
	radius(50.0f)
{
	position = {x, y};

	shape.setRadius(radius);
	shape.setFillColor(sf::Color::Transparent);
	//shape.setFillColor(sf::Color(129,128,128));
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

void Asteroid::setRandomSizeAndSpeed()
{
	float chance = BrightRandom::range(0, 100);
	size = SMALL_SIZE;
	size = chance < SMALL_SIZE_CHANCE ? SMALL_SIZE : MEDIUM_SIZE;
	size = chance < SMALL_SIZE_CHANCE + MEDIUM_SIZE_CHANCE ? size : LARGE_SIZE;
	shape.setRadius(size);
	
	speed = size <= SMALL_SIZE ? HIGH_SPEED : MEDIUM_SPEED;
	speed = size <= MEDIUM_SIZE ? speed : LOW_SPEED;
}

bool Asteroid::canBreak()
{
	if (size > SMALL_SIZE)
	{
		return true;
	}
	return false;
}
