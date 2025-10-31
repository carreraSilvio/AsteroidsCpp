#include "Services.h"

Services::Services() 
{
    //Core Services
    inputService = std::make_unique<BrightInputService>();
    viewManager = std::make_unique<BrightViewManager>();
    //audioManager = std::make_unique<AudioManager>();

    //Game Services
    highscoreService = std::make_unique<HighscoreService>();
}

Services::~Services() 
{
    viewManager.reset();
    //audioManager.reset();
}