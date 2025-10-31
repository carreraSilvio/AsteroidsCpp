#ifndef TITLEVIEW_H
#define TITLEVIEW_H

#include <SFML/Graphics.hpp>
#include "BrightLib/BrightUI/BrightView.h"

class TitleView : public BrightView
{
public:

	sf::Text scorePlayer1;
	sf::Text pressStart;

	TitleView();

	void draw(sf::RenderWindow& window);
};

#endif // TITLEVIEW_H