#pragma once

#include <SFML/Graphics.hpp>
#include "BrightLib/BrightEntity.h"

class Bullet : public BrightEntity
{
public:
	float speed;
	sf::Vector2f direction;
	sf::CircleShape shape;

	//functions
	Bullet(float x, float y);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f);
};