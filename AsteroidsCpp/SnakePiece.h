#ifndef SNAKEPIECE_H
#define SNAKEPIECE_H

#include <SFML/Graphics.hpp>

class SnakePiece
{
public: 
	sf::Vector2f position;

	float width, height;
	sf::RectangleShape shape;

	SnakePiece(float x, float y);

	void setPosition(sf::Vector2f);
	void setPosition(float x, float y);
};

#endif // SNAKEPIECE_H