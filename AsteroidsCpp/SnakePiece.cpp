#include "SnakePiece.h"
#include "GameConstants.h"

SnakePiece::SnakePiece(float x, float y)
{
	position.x = x;
	position.y = y;

	width = GameConstants::SNAKE_PIECE_SIZE;
	height = GameConstants::SNAKE_PIECE_SIZE;

	shape.setSize({ width, height });
	shape.setFillColor(sf::Color::White);
	shape.setPosition(sf::Vector2(x, y));
}

void SnakePiece::setPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}
void SnakePiece::setPosition(float x, float y)
{
	position = { x,y };
	shape.setPosition(position);
}

