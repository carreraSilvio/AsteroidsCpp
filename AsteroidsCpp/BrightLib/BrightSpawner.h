#pragma once
#include <SFML/Graphics.hpp>
#include "BrightPool.h"
#include "BrightEntity.h"
#include "BrightEvent.h"

/// <summary>
/// Responsible for spawning objects every given interval.
/// </summary>
template<class T>
class BrightSpawner : public BrightEntity
{
public:
	BrightEvent<T&> onSpawn;

	BrightSpawner(size_t poolSize, float spawnInterval) 
		: pool(poolSize), 
		spawnTimer(0.0f),
		spawnInterval(spawnInterval) {}

	void update(float dt) 
	{
		if (!active)
		{
			return;
		}

		spawnTimer += dt;
		if (spawnTimer >= spawnInterval)
		{
			T& spawned = pool.getAvailable();
			spawned.active = true;
			onSpawn.fire(spawned);
			spawnTimer = 0.0f;
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

	float spawnTimer;
	float spawnInterval;
};

