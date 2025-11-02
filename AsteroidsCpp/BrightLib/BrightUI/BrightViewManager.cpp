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
	for (auto view : openedViews)
	{
		view.second->update(dt);
	}
}

void BrightViewManager::draw(sf::RenderWindow& window)
{
	for (auto view : openedViews)
	{
		view.second->draw(window);
	}
}
