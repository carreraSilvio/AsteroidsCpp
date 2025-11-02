#pragma once

#include <SFML/Graphics.hpp>
#include "BrightLib/BrightEntity.h"
#include "BrightLib/BrightTimer.h"

class Bullet : public BrightEntity
{
public:
	float speed;
	sf::Vector2f direction;
	sf::CircleShape shape;

	BrightTimer lifetimeTimer;

	//functions
	Bullet(float x, float y);
	Bullet() : Bullet(0, 0) {};
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f);

private:
	inline static constexpr float LIFETIME_DURATION = 2.5f;
};