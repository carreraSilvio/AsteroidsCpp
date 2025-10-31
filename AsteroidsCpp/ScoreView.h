#ifndef SCOREVIEW_H
#define SCOREVIEW_H

#include <SFML/Graphics.hpp>
#include "BrightLib/BrightUI/BrightView.h"

class ScoreView : public BrightView
{
public:


	ScoreView();

	void setScore(unsigned int score);
	void setHighscore(unsigned int highscore);

	void draw(sf::RenderWindow& window);

private:
	sf::Text playerScore;
	sf::Text playerHighscore;
};

#endif // SCOREVIEW_H