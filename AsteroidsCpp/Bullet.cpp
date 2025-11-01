#include "Bullet.h"

Bullet::Bullet(float x, float y)
	: BrightEntity(),
	speed(300.0f),
	lifetimeTimer(0.0f)
{
	position = { x, y };

	shape.setRadius(5);
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(sf::Vector2(x, y));
}

void Bullet::update(float dt)
{
	if (!active)
	{
		return;
	}

	position += speed * direction *  dt;

	shape.setPosition(position);

	lifetimeTimer += dt;
	if (lifetimeTimer > LIFETIME_DURATION)
	{
		lifetimeTimer = 0.0f;
		active = false;
	}
}

void Bullet::draw(sf::RenderWindow& window)
{
	if (!active)
	{
		return;
	}

	window.draw(shape);
}

void Bullet::setPosition(float x, float y)
{
	position = { x,y };
	setPosition(position);
}
void Bullet::setPosition(sf::Vector2f position)
{
	this->position = position;
	shape.setPosition(position);
}