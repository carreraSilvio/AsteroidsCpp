#pragma once

#include "BrightLib/BrightState.h"
#include "Snake.h"
#include "Fruit.h"
#include "ScoreView.h"

class Play_GameState : public BrightState
{
public:
	unsigned int playerScore = 0;
	Snake snake;
	Fruit fruit;

	float playerAteFruitTimer = 0.0f;
	float playerDiedTimer = 0.0f;

	//UI
	ScoreView* scoreView;

	Play_GameState();
	void enter();
	std::type_index update(float);
	void draw(sf::RenderWindow&);

private:
	enum class GameState
	{
		Playing = 0,
		PlayerAteFruit = 1,
		DelayAfterEatingFruit = 2,
		PlayerDied = 3,
		DelayAfterPlayerDied,
	};
	GameState subState = GameState::Playing;

	void handleSnakeReachScreenEdge();

	sf::Vector2f getRandomFreePosition(const Snake& snake);
};

