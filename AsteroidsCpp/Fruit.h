#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>
#include "BrightLib/BrightEvent.h"

class Fruit
{
public:
	//members
	float startX, startY;
	sf::Vector2f position;
	float radius;
	bool active;

	sf::CircleShape  shape;

	//functions
	Fruit(float x, float y);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	
	void resetPosition();

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f);

};

#endif // FRUIT_H