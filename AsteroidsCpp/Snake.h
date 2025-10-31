#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include "SnakePiece.h"
#include <deque>
#include "BrightLib/BrightEvent.h"

class Snake
{
private:
	static const int PIECE_OFFSET = 1;

public: 
	//events
	BrightEvent<> onReachScreenEdge;

	//members
	std::vector<SnakePiece> pieces;
	sf::Vector2i direction;

	std::deque<sf::Vector2f> path;
	float speed;

	Snake(float x, float y);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPositionAtDistance(float d);
	void resetPosition();
	void grow();

	SnakePiece getHead();

	void setPosition(sf::Vector2f);
	void setPosition(float x, float y);
};

#endif // SNAKE_H