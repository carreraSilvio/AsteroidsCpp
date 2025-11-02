#pragma once
#include <SFML/Graphics.hpp>
#include <typeindex>

class BrightView
{
public:
	BrightView(const std::type_index& t) : typeId(t) {}

	const std::type_index& getTypeId() const { return typeId; }

	virtual void open();
	virtual void update(float);
	void draw(sf::RenderWindow&);
	virtual void close();

	sf::Text& addText();

protected:
	const std::type_index typeId;
	std::list<sf::Text> texts;
};