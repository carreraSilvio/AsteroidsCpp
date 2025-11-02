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
	BrightSpawner(size_t poolSize, float spawnInterval) 
		: pool(poolSize), 
		spawnTimer(spawnInterval) {}

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
		T& spawned = pool.getAvailable();
		spawned.position = position;
		spawned.active = true;
		onSpawn.fire(spawned);
		return spawned;
	}

	void spawn(unsigned int spawnAmount)
	{
		while (spawnAmount > 0)
		{
			spawn();
			spawnAmount--;
		}
	}

	T& spawnAt(sf::Vector2f position)
	{
		T& spawned = spawn();
		spawned.position = position;
		return spawned;
	}

	void spawnAt(sf::Vector2f position, unsigned int spawnAmount)
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

	//todo: temp, should be private
	BrightPool<T> pool;

private:
	BrightTimer spawnTimer;
};

