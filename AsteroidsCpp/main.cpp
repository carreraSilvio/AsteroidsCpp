#include <SFML/Graphics.hpp>
#include "GameConstants.h"
#include "BrightLib/BrightFSM.h"
#include "Play_GameState.h"
#include "Title_GameState.h"
#include "Services.h"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({ GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT }), 
        "Bright Snake");
    sf::Clock deltaClock;

    //initialize service locator
    Services services;

    //load save game
    services.Highscore().load();

    //initialize game
    BrightFSM gameFsm;
    gameFsm.setInitialState<Title_GameState>();
    gameFsm.addState<Play_GameState>();
    gameFsm.enterInitialState();

    while (window.isOpen())
    {
        //CHECK FOR EXIT
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = deltaClock.restart().asSeconds();

        //UPDATE
        gameFsm.update(dt);
        
        //DRAW
        window.clear();
        gameFsm.draw(window);
        window.display();
    }

}