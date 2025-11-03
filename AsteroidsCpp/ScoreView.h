#pragma once

#include <SFML/Graphics.hpp>
#include "BrightLib/BrightUI/BrightView.h"

class ScoreView : public BrightView
{
public:
	ScoreView();

	void setScore(int score);
	void setHighscore(int highscore);

private:
	sf::Text& playerScore;
	sf::Text& playerHighscore;
};