#pragma once

/// <summary>
/// Responsible for managing an array entities to allow them to be easily reused.
/// </summary>
template<class T>
class BrightPool
{
public:
	BrightPool(size_t poolSize): poolSize(poolSize), entities(poolSize)
	{
		for(T& entity : entities)
		{
			entity.active = false;
		}
	}

	/// <summary>
	/// Retuns an entity that's available to be used. Which here means its active flag is false.
	/// </summary>
	T& getAvailable()
	{
		for (int i = 0; i < poolSize; i++)
		{
			if (!entities[i].active)
			{
				return entities[i];
			}
		}
		//todo: return null or always grow
		return entities[0];
	}

	//temp, remove
	std::vector<T>& getAll()
	{
		return entities;
	}

private:
	std::vector<T> entities;
	size_t poolSize;
};

