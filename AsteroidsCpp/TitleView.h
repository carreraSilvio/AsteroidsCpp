#ifndef TITLEVIEW_H
#define TITLEVIEW_H

#include <SFML/Graphics.hpp>
#include "BrightLib/BrightUI/BrightView.h"

class TitleView : public BrightView
{
public:

	sf::Text& gameTitle;
	sf::Text& pressStart;
	sf::Text& credits;

	TitleView();
};

#endif // TITLEVIEW_H