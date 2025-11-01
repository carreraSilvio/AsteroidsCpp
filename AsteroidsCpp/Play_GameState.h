#pragma once

#include "BrightLib/BrightState.h"
#include "BrightLib/BrightPool.h"
#include "Ship.h"
#include "Asteroid.h"
#include "ScoreView.h"
#include "Bullet.h"

class Play_GameState : public BrightState
{
public:
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

	Ship ship;
	Asteroid asteroid;
	BrightPool<Bullet> bullets;

	unsigned int playerScore = 0;
	float playerAteFruitTimer = 0.0f;
	float playerDiedTimer = 0.0f;

	//UI
	ScoreView* scoreView;

	void handlePlayerShoot();

	sf::Vector2f getRandomFreePosition(const Ship& ship);
};

