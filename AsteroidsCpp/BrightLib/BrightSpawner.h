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
			T& spawned = pool.getAvailable();
			spawned.active = true;
			onSpawn.fire(spawned);
			spawnTimer.reset();
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

