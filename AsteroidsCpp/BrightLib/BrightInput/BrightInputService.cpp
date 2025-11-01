#include "BrightInputService.h"
#include <iostream>

BrightInputService::BrightInputService()
{
	//default bindings
    bindKey(BrightActionButton::MOVE_UP, sf::Keyboard::Key::Up);
    bindKey(BrightActionButton::MOVE_UP, sf::Keyboard::Key::W);
    bindKey(BrightActionButton::MOVE_DOWN, sf::Keyboard::Key::Down);
    bindKey(BrightActionButton::MOVE_DOWN, sf::Keyboard::Key::S);
    bindKey(BrightActionButton::MOVE_LEFT, sf::Keyboard::Key::Left);
    bindKey(BrightActionButton::MOVE_LEFT, sf::Keyboard::Key::A);
    bindKey(BrightActionButton::MOVE_RIGHT, sf::Keyboard::Key::Right);
    bindKey(BrightActionButton::MOVE_RIGHT, sf::Keyboard::Key::D);
}

void BrightInputService::bindKey(BrightActionButton action, sf::Keyboard::Key key)
{
	actionToKeys[action].push_back(key);
}

bool BrightInputService::isButtonPressed(BrightActionButton action)
{
    auto it = actionToKeys.find(action);
    if (it == actionToKeys.end())
    {
        //tbd std::cerr << "[Warning] Input: action button " << action  << " not mapped.";
        //std::cerr << "[Warning] Input: action button not mapped.";
        //OutputDebugStringA(("[Warning] Input: action button not mapped.").c_str());
        return false;
    }

    for (sf::Keyboard::Key key : it->second)
    {
        if (sf::Keyboard::isKeyPressed(key))
        {
            return true;
        }
    }
    return false;
}
