#pragma once
#include <SFML/Graphics.hpp>

class BrightEntity
{
public:
	bool active;
	sf::Vector2f position;

	BrightEntity();

	unsigned int getId() { return id; }

private:
	unsigned int id;
	static unsigned int NEXT_ID;
};

