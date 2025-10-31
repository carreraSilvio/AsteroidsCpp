#include "TitleView.h"
#include <stdexcept>
#include "BrightLib/BrightUI/BrightViewManager.h"
#include "GameConstants.h"

TitleView::TitleView() : BrightView(typeid(TitleView)),
    scorePlayer1(BrightViewManager::DEFAULT_FONT),
    pressStart(BrightViewManager::DEFAULT_FONT)
{
    scorePlayer1.setString("BRIGHT SNAKE");
    scorePlayer1.setCharacterSize(BrightViewManager::DEFAULT_FONT_SIZE * 2);
    scorePlayer1.setFillColor(sf::Color::White);
    scorePlayer1.setPosition(sf::Vector2f(GameConstants::WindowHalfSize().x - (scorePlayer1.getLocalBounds().size.x / 2.0f), 200.0f));

    pressStart.setString("[PRESS ENTER]");
    pressStart.setCharacterSize(BrightViewManager::DEFAULT_FONT_SIZE);
    pressStart.setFillColor(sf::Color::White);
    pressStart.setPosition(sf::Vector2f(GameConstants::WindowHalfSize().x - (pressStart.getLocalBounds().size.x/2.0f), GameConstants::WindowHalfSize().y));
}

void TitleView::draw(sf::RenderWindow& window)
{
    window.draw(scorePlayer1);
    window.draw(pressStart);
}
