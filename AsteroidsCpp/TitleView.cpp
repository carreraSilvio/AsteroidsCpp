#include "TitleView.h"
#include <stdexcept>
#include "BrightLib/BrightUI/BrightViewManager.h"
#include "GameConstants.h"

TitleView::TitleView() : BrightView(typeid(TitleView)),
    gameTitle(addText()),
    pressStart(addText()),
    credits(addText())
{
    gameTitle.setString("ASTEROIDS");
    gameTitle.setCharacterSize(BrightViewManager::DEFAULT_FONT_SIZE_LARGE * 2);
    gameTitle.setPosition({ 
        GameConstants::WindowHalfSize().x - (gameTitle.getLocalBounds().size.x / 2.0f), 
        GameConstants::WindowHalfSize().y - 100.0f
        });

    pressStart.setString("[PRESS ENTER]");
    pressStart.setPosition({ 
        GameConstants::WindowHalfSize().x - (pressStart.getLocalBounds().size.x / 2.0f),
        GameConstants::WindowHalfSize().y 
        });

    credits.setString("brightflask - 2025");
    credits.setCharacterSize(BrightViewManager::DEFAULT_FONT_SIZE_SMALL * 0.75f);
    credits.setPosition({ 
        GameConstants::WindowHalfSize().x - (credits.getLocalBounds().size.x / 2.0f), 
        GameConstants::WINDOW_HEIGHT - credits.getLocalBounds().size.y - 10
        });
}
