#include "BrightView.h"
#include "BrightViewManager.h"

void BrightView::open()
{
}

void BrightView::update(float dt)
{

}

void BrightView::draw(sf::RenderWindow& window)
{
	for (sf::Text& text : texts)
	{
		window.draw(text);
	}
}

void BrightView::close()
{
}

sf::Text& BrightView::addText()
{
	sf::Text text(BrightViewManager::DEFAULT_FONT, "", BrightViewManager::DEFAULT_FONT_SIZE_MEDIUM);
	text.setFillColor(sf::Color::White);
	texts.push_back(text);
	return texts.back();
}
