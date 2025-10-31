#include "Snake.h"
#include "GameConstants.h"
#include "Services.h"

Snake::Snake(float x, float y)
{
	direction = {1, 0};
	speed = 250.0f;

	SnakePiece head(x, y);
	pieces.push_back(head);

	for (int i = 1; i < 3; i++)
	{
		SnakePiece tail(x - GameConstants::SNAKE_PIECE_SIZE * i, y);
		pieces.push_back(tail);
	}
}

void Snake::resetPosition()
{
	direction = { 1, 0 };
	
	//remove pieces
	while (pieces.size() > 3)
	{
		pieces.pop_back();
	}

	//reset position
	setPosition(GameConstants::WINDOW_WIDTH / 2, GameConstants::WINDOW_HEIGHT / 2);
}

void Snake::update(float dt)
{
	if (Services::Input().isButtonPressed(BrightActionButton::MOVE_UP)
		&& direction.y != 1)
	{
		direction.x = 0;
		direction.y = -1;
	}
	else if (Services::Input().isButtonPressed(BrightActionButton::MOVE_DOWN)
		&& direction.y != -1)
	{
		direction.x = 0;
		direction.y = 1;
	}
	else if (Services::Input().isButtonPressed(BrightActionButton::MOVE_LEFT)
		&& direction.x != 1)
	{
		direction.x = -1;
		direction.y = 0;
	}
	else if (Services::Input().isButtonPressed(BrightActionButton::MOVE_RIGHT)
		&& direction.x != -1)
	{
		direction.x = 1;
		direction.y = 0;
	}

	// move head
	sf::Vector2f moveDelta = { direction.x * speed * dt, direction.y * speed * dt };
	sf::Vector2f newHeadPosition = pieces[0].position + moveDelta;

	if (newHeadPosition.x < 0) 
	{
		onReachScreenEdge.fire();
	}
	else if (newHeadPosition.x >= GameConstants::WINDOW_WIDTH)
	{
		onReachScreenEdge.fire();
	}
	else if (newHeadPosition.y < 0) 
	{
		onReachScreenEdge.fire();
	}
	else if (newHeadPosition.y >= GameConstants::WINDOW_HEIGHT) 
	{
		onReachScreenEdge.fire();
	}

	pieces[0].position = newHeadPosition;
	pieces[0].shape.setPosition(pieces[0].position);

	// record head path
	path.push_front(pieces[0].position);
	float segmentDistance = GameConstants::SNAKE_PIECE_SIZE + PIECE_OFFSET; //offset

	// move each segment along path spaced by segmentDistance
	float distance = 0.f;
	for (size_t i = 1; i < pieces.size(); ++i)
	{
		distance += segmentDistance;
		pieces[i].setPosition(getPositionAtDistance(distance));
	}

	// trim path (keep small buffer)
	if (path.size() > 1000)
	{
		path.resize(1000);
	}
}

sf::Vector2f Snake::getPositionAtDistance(float d)
{
	float traveled = 0.f;
	for (size_t i = 1; i < path.size(); ++i)
	{
		float dx = path[i].x - path[i - 1].x;
		float dy = path[i].y - path[i - 1].y;
		float segLenSq = dx * dx + dy * dy;

		// Use squared distance comparison to avoid sqrt
		if (traveled * traveled + segLenSq >= d * d)
		{
			return path[i];
		}

		traveled += std::sqrt(segLenSq);
	}
	return path.back();
}

void Snake::draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < pieces.size(); ++i)
	{
		window.draw(pieces[i].shape);
	}
}

void Snake::grow()
{
	sf::Vector2f newPiecePosition = pieces.back().position;
	newPiecePosition.x += GameConstants::SNAKE_PIECE_SIZE * (direction.x * -1);
	newPiecePosition.y += GameConstants::SNAKE_PIECE_SIZE * (direction.y * -1);

	SnakePiece newPiece(newPiecePosition.x, newPiecePosition.y);
	pieces.push_back(newPiece);
}

SnakePiece Snake::getHead()
{
	return pieces.front();
}

void Snake::setPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

void Snake::setPosition(float x, float y)
{
	pieces[0].position = {x, y};

	path.push_front(pieces[0].position);
	path.push_front(pieces[0].position - sf::Vector2f(GameConstants::SNAKE_PIECE_SIZE, 0));
	path.push_front(pieces[0].position - sf::Vector2f(GameConstants::SNAKE_PIECE_SIZE * 2, 0));
	for (int i = 1; i < 3; i++)
	{
		pieces[i].setPosition(path[i]);
	}
}
