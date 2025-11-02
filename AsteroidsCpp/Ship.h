#pragma once

#include <SFML/Graphics.hpp>
#include "BrightLib/BrightEntity.h"
#include "BrightLib/BrightEvent.h"
#include "BrightLib/BrightTimer.h"

class Ship : public BrightEntity
{
public: 
	//events
	BrightEvent<> onShoot;

	//members
	sf::Vector2f velocity;
	sf::Angle rotation;

	float thrust;
	float linerDamping;
	
	const sf::Angle rotationSpeed = sf::degrees(180.f);//degrees per second

	sf::ConvexShape shape;

	Ship(float x, float y);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	void resetPosition();

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f);

	const sf::Vector2f getFrontPoint();
	const sf::Vector2f getForwardVector();

private:
	BrightTimer shootTimer;
	inline static constexpr float SHOOT_INTERVAL = 0.3f;
};