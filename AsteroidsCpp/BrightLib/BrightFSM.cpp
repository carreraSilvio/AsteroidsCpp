#include "BrightFSM.h"

BrightFSM::BrightFSM() :
	currentState(nullptr),
	initialStateTypeId(typeid(nullptr)),
	nextStateTypeId(typeid(nullptr))
{
}

void BrightFSM::enterInitialState()
{
	if (currentState == nullptr)
	{
		currentState = states[initialStateTypeId].get();
		currentState->enter();
		nextStateTypeId = currentState->getTypeId();
	}
}

void BrightFSM::update(float dt)
{
	if (currentState == nullptr)
	{
		return;
	}

	std::type_index candidateTypeId = currentState->update(dt);
	if (candidateTypeId != nextStateTypeId)
	{
		nextStateTypeId = candidateTypeId;  // defer transition
	}
}

void BrightFSM::draw(sf::RenderWindow& window)
{
	if (currentState == nullptr)
	{
		return;
	}

	currentState->draw(window);

	// apply transition *after* drawing
	if (nextStateTypeId != currentState->getTypeId())
	{
		currentState->exit();
		currentState = states[nextStateTypeId].get();
		currentState->enter();
		nextStateTypeId = currentState->getTypeId();
	}
}
