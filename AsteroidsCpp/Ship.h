#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>
#include "BrightLib/BrightEvent.h"

class Ship
{
public: 
	//events
	BrightEvent<> onReachScreenEdge;

	//members
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Angle rotation;

	float thrust;
	float linerDamping;
	/// <summary>
	/// degrees per second
	/// </summary>
	const sf::Angle rotationSpeed = sf::degrees(180.f);

	sf::ConvexShape shape;

	Ship(float x, float y);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	void resetPosition();

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f);

private:

};

#endif // SHIP_H