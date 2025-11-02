#pragma once
#include "BrightPool.h"
#include "BrightEntity.h"
#include "BrightEvent.h"
#include "BrightTimer.h"

/// <summary>
/// Responsible for spawning objects every given interval.
/// </summary>
template<class T>
class BrightSpawner : public BrightEntity
{
public:
	//events
	BrightEvent<T&> onSpawn;

	//constructor
	BrightSpawner(size_t poolSize, float spawnInterval, float spawnIntervalOffset = 0.0f) 
		: pool(poolSize), 
		spawnTimer(spawnInterval, spawnIntervalOffset),
		spawnPoints(){}

	void update(float dt) 
	{
		if (!active)
		{
			return;
		}

		if (spawnTimer.update(dt))
		{
			spawn();
			spawnTimer.reset();
		}
	}

	T& spawn()
	{
		sf::Vector2f newPosition = spawnPoints.empty() ? 
			position
			: BrightRandom::range<sf::Vector2f>(spawnPoints);
		return spawnAt(newPosition);
	}

	void spawn(unsigned int spawnAmount)
	{
		while (spawnAmount > 0)
		{
			spawn();
			spawnAmount--;
		}
	}

	T& spawnAt(const sf::Vector2f& position)
	{
		T& spawned = pool.getAvailable();
		spawned.position = position;
		spawned.active = true;
		onSpawn.fire(spawned);
		return spawned;
	}

	void spawnAt(const sf::Vector2f& position, unsigned int spawnAmount)
	{
		while (spawnAmount > 0)
		{
			spawnAt(position);
			spawnAmount--;
		}
	}

	void despawnAll()
	{
		for (T& entry : pool.getAll())
		{
			entry.active = false;
			//entry.OnDespawn();
		}
	}

	void addSpawnPoint(sf::Vector2f newSpawnPoint)
	{
		spawnPoints.push_back(newSpawnPoint);
	}

	//todo: temp, should be private
	BrightPool<T> pool;

private:
	BrightTimer spawnTimer;
	std::vector<sf::Vector2f> spawnPoints;
};

