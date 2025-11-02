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
	/// Gets an entity available to be used. For now: Available means the entity is not active.
	/// </summary>
	T& getAvailable()
	{
		for (size_t i = 0; i < poolSize; i++)
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
	
	void deactivateAll()
	{
		for (size_t i = 0; i < poolSize; i++)
		{
			entities[i].active = false;
		}
	}

private:
	std::vector<T> entities;
	size_t poolSize;
};

