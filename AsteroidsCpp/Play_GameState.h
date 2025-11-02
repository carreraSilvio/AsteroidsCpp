#pragma once

#include "BrightLib/BrightState.h"
#include "BrightLib/BrightPool.h"
#include "BrightLib/BrightSpawner.h"
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
		Playing,
		PlayerDead,
		DelayAfterPlayerDead,
	};
	GameState subState = GameState::Playing;

	Ship ship;
	BrightSpawner<Asteroid> asteroidSpawner;
	BrightPool<Bullet> bullets;

	unsigned int playerScore = 0;
	float playerAteFruitTimer = 0.0f;
	float playerDiedTimer = 0.0f;

	//UI
	ScoreView* scoreView;

	//event handlers
	void handlePlayerShoot();
	void handleAsteroidSpawn(Asteroid& asteroid);

	sf::Vector2f getRandomFreePosition(const Ship& ship);
};

