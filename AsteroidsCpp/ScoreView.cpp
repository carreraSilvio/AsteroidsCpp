#include "ScoreView.h"
#include <stdexcept>
#include "BrightLib/BrightUI/BrightViewManager.h"
#include "GameConstants.h"

ScoreView::ScoreView() : BrightView(typeid(ScoreView)),
    playerScore(addText()),
    playerHighscore(addText())
{
    playerScore.setFillColor(sf::Color::White);
    playerScore.setString("0");
    playerScore.setPosition(sf::Vector2f(10.0f, 10.0f));
    setScore(0);

    playerHighscore.setFillColor(sf::Color::Yellow);
    setHighscore(0);
}

void ScoreView::setScore(unsigned int score)
{
    playerScore.setString(std::to_string(score));
    float x = (GameConstants::WINDOW_WIDTH / 2.0f) - 50.0f;
    float y = 10.0f;
    playerScore.setPosition(sf::Vector2f(x, y));
}

void ScoreView::setHighscore(unsigned int highscore)
{
    playerHighscore.setString(std::to_string(highscore));
    float x = (GameConstants::WINDOW_WIDTH / 2.0f) + 50.0f;
    float y = 10.0f;
    playerHighscore.setPosition(sf::Vector2f(x, y));
}
