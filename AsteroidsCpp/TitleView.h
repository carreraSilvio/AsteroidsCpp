#pragma once

#include <SFML/Graphics.hpp>
#include "BrightLib/BrightUI/BrightView.h"
#include "BrightLib/BrightTimer.h"

class TitleView : public BrightView
{
public:
	TitleView();

	void update(float dt);

private:
	sf::Text& gameTitle;
	sf::Text& pressStart;
	sf::Text& credits;

	BrightTimer blinkTimer;
};