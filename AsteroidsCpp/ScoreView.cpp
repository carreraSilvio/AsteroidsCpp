#include "ScoreView.h"
#include "BrightLib/BrightUI/BrightViewManager.h"
#include "GameConstants.h"

ScoreView::ScoreView() : BrightView(typeid(ScoreView)),
    playerScore(addText()),
    playerHighscore(addText())
{
    //score
    sf::Text& playerScoreTitle = addText("SCORE", BrightViewManager::DEFAULT_FONT_SIZE_SMALL);
    playerScoreTitle.setPosition({ (GameConstants::WINDOW_WIDTH / 2.0f) - 120.0f, 0.0f });

    playerScore.setCharacterSize(BrightViewManager::DEFAULT_FONT_SIZE_SMALL);
    playerScore.setFillColor(sf::Color::White);
    playerScore.setString("0");
    setScore(0);

    //highscore
    sf::Text& playerHighscoreTitle = addText("HIGH", BrightViewManager::DEFAULT_FONT_SIZE_SMALL);
    playerHighscoreTitle.setPosition({ (GameConstants::WINDOW_WIDTH / 2.0f) + 50.0f, 0.0f });
    playerHighscoreTitle.setFillColor(sf::Color::Yellow);

    playerHighscore.setCharacterSize(BrightViewManager::DEFAULT_FONT_SIZE_SMALL);
    playerHighscore.setFillColor(sf::Color::Yellow);
    playerHighscore.setString("0");
    setHighscore(0);

    //set background
    backgroundRectangle.setPosition({ 0,0 });
    backgroundRectangle.setSize({ GameConstants::WINDOW_WIDTH, 30 });
}

void ScoreView::setScore(int score)
{
    playerScore.setString(std::to_string(score));
    float x = (GameConstants::WINDOW_WIDTH / 2.0f) - 50.0f;
    float y = 0.0f;
    playerScore.setPosition({ x, y });
}

void ScoreView::setHighscore(int highscore)
{
    playerHighscore.setString(std::to_string(highscore));
    float x = (GameConstants::WINDOW_WIDTH / 2.0f) + 100.0f;
    float y = 0.0f;
    playerHighscore.setPosition({ x, y });
}
