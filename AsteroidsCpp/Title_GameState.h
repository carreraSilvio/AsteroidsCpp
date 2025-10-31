#pragma once

#include "BrightLib/BrightState.h"
#include "TitleView.h"

class Title_GameState : public BrightState
{
public:
	TitleView* titleView;

	Title_GameState();
	void enter();
	std::type_index update(float);
	void draw(sf::RenderWindow&);
};

