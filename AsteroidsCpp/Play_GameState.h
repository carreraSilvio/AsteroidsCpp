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
	void exit();
	std::type_index update(float);
	void draw(sf::RenderWindow&);

private:
	enum class GameState
	{
		Playing,
		PlayerDead,
		RestartingGame,
	};
	GameState subState = GameState::Playing;

	Ship ship;
	BrightSpawner<Asteroid> asteroidSpawner;
	BrightPool<Bullet> bullets;

	int playerScore = 0;
	BrightTimer restartGameTimer;

	//UI
	ScoreView* scoreView;

	void increaseScore(Asteroid::Size asteroidSize);
	void setScore(int mewScore);

	//event handlers
	void handlePlayerShoot();
	void handleAsteroidSpawn(Asteroid& asteroid);
	void handleDynamicAsteroidSpawn(Asteroid& asteroid);

	sf::Vector2f getRandomFreePosition(const Ship& ship);
};

