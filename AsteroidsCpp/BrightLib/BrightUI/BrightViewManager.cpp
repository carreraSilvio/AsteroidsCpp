#include "BrightViewManager.h"

BrightViewManager::BrightViewManager()
{
	if (!DEFAULT_FONT.openFromFile(DEFAULT_FONT_PATH))
	{
		throw std::runtime_error("Failed to load font: " + DEFAULT_FONT_PATH);
	}
}

void BrightViewManager::update(float dt)
{
	for (size_t i = 0; i < openedViews.size(); ++i)
	{
		openedViews[i]->update(dt);
	}
}

void BrightViewManager::draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < openedViews.size(); ++i)
	{
		openedViews[i]->draw(window);
	}
}
