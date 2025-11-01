#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>
#include "BrightLib/BrightEvent.h"
#include "BrightLib/BrightEntity.h"

class Asteroid : public BrightEntity
{
public:
	//members
	float speed;
	sf::Vector2f direction;

	float radius;
	sf::CircleShape shape;

	//functions
	Asteroid(float x, float y);
	Asteroid() : Asteroid(0, 0) {};
	void update(float dt);
	void draw(sf::RenderWindow& window);
	
	void resetPosition();

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f);

};

#endif // ASTEROID_H