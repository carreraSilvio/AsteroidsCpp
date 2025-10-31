#pragma once
#include <SFML/Graphics.hpp>
#include <typeindex>
#include "BrightUI/BrightViewManager.h"

class BrightState
{
protected:
	const std::type_index typeId;

public:
	BrightState(const std::type_index& t) : typeId(t) {}

	const std::type_index& getTypeId() const { return typeId; }

	virtual void enter();
	virtual std::type_index update(float);
	virtual void draw(sf::RenderWindow&);
	virtual void exit();
};