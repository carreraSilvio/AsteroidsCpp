#include "Asteroid.h"
#include "GameConstants.h"
#include "BrightLib/BrightRandom.h"

Asteroid::Asteroid(float x, float y) 
	: BrightEntity(),
	size(Asteroid::Size::Small),
	speed(HIGH_SPEED),
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

void Asteroid::setRandomSize()
{
	float chance = BrightRandom::range(0, 100);
	Asteroid::Size newSize;
	if (chance < SMALL_SIZE_CHANCE)
	{
		newSize = Asteroid::Size::Small;
	}
	else if (chance < SMALL_SIZE_CHANCE + MEDIUM_SIZE_CHANCE)
	{
		newSize = Asteroid::Size::Medium;
	}
	else
	{
		newSize = Asteroid::Size::Large;
	}
	setSize(newSize);
}

void Asteroid::setSize(Asteroid::Size newSize)
{
	switch (newSize)
	{
	case Asteroid::Size::Small:
		shape.setRadius(SMALL_SIZE);
		speed = HIGH_SPEED;
		break;

	case Asteroid::Size::Medium:
		shape.setRadius(MEDIUM_SIZE);
		speed = MEDIUM_SPEED;
		break;

	case Asteroid::Size::Large:
		shape.setRadius(LARGE_SIZE);
		speed = LOW_SPEED;
		break;
	}
	size = newSize;
}


bool Asteroid::canBreak()
{
	if (size == Asteroid::Size::Small)
	{
		return false;
	}
	return true;
}
