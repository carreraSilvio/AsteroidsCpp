#pragma once
#include <SFML/Graphics.hpp>
#include <typeindex>

class BrightView
{
protected:
	const std::type_index typeId;

public:
	BrightView(const std::type_index& t) : typeId(t) {}

	const std::type_index& getTypeId() const { return typeId; }

	virtual void open();
	virtual void update(float);
	virtual void draw(sf::RenderWindow&);
	virtual void close();
};