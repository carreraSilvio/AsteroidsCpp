#include "BrightState.h"




void BrightState::enter()
{
}

std::type_index BrightState::update(float dt)
{
	return getTypeId();
}

void BrightState::draw(sf::RenderWindow&)
{
}

void BrightState::exit()
{
}
