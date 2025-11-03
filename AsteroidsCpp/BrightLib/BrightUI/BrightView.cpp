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
	window.draw(backgroundRectangle);
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
	return addText("", BrightViewManager::DEFAULT_FONT_SIZE_MEDIUM);
}

sf::Text& BrightView::addText(std::string textValue, const unsigned int fontSize)
{
	sf::Text text(BrightViewManager::DEFAULT_FONT, textValue, fontSize);
	text.setFillColor(sf::Color::White);
	texts.push_back(text);
	return texts.back();
}
