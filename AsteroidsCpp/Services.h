#pragma once

#include "BrightLib/BrightUI/BrightViewManager.h"
#include "BrightLib/BrightInput/BrightInputService.h"
#include "HighscoreService.h"

class Services 
{
public:
    Services(); 
    ~Services();         

    //Core and generic
    static BrightInputService& Input() { return *inputService; }
    static BrightViewManager& Views() { return *viewManager; }
    //static AudioManager& audio() { return *audioManager; }

    //Game-dependent
    static HighscoreService& Highscore() { return *highscoreService; }

private:
    static inline std::unique_ptr<BrightInputService> inputService;
    static inline std::unique_ptr<BrightViewManager> viewManager;
    //static inline std::unique_ptr<AudioManager> audioManager;

    static inline std::unique_ptr<HighscoreService> highscoreService;
};
