#pragma once

#include <SFML/Graphics.hpp>
#include "BrightLib/BrightEntity.h"
#include "BrightLib/BrightEvent.h"
#include "BrightLib/BrightTimer.h"

class Asteroid : public BrightEntity
{
public:
	enum class Size 
	{
		Small,
		Medium,
		Large
	};

	//members
	Size size;
	float speed;
	sf::Vector2f direction;

	float radius;
	sf::CircleShape shape;
	BrightTimer lifetimeTimer; 

	//functions
	Asteroid(float x, float y);
	Asteroid() : Asteroid(0, 0) {};
	void update(float dt);
	void draw(sf::RenderWindow& window);
	
	void resetPosition();

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f);

	/// <summary>
	/// Sets a random size based on the odds set. Also affects speed.
	/// </summary>
	void setRandomSize();

	/// <summary>
	/// Sets the asteroid size. Also affects speed.
	/// </summary>
	void setSize(Asteroid::Size size);

	bool canBreak();

private:
	inline static constexpr float SMALL_SIZE = 10.0f;
	inline static constexpr float MEDIUM_SIZE = 30.0f;
	inline static constexpr float LARGE_SIZE = 50.0f;
	static const unsigned int SMALL_SIZE_CHANCE = 50.0f;
	static const unsigned int MEDIUM_SIZE_CHANCE = 30.0f;

	inline static constexpr float LOW_SPEED = 50.0f;
	inline static constexpr float MEDIUM_SPEED = 80.0f;
	inline static constexpr float HIGH_SPEED = 150.0f;

	inline static constexpr float LIFETIME_DURATION = 2.5f;
};