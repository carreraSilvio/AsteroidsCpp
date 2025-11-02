#include <typeindex>
#include "Title_GameState.h"
#include "Play_GameState.h"
#include "Services.h"

Title_GameState::Title_GameState() : BrightState(typeid(Title_GameState))
{
    //UI
    titleView = Services::Views().addView<TitleView>();
}

void Title_GameState::enter()
{
    Services::Views().openView<TitleView>();
}

void Title_GameState::exit()
{
    Services::Views().closeView<TitleView>();
    //titleView->close();
}

std::type_index Title_GameState::update(float)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    {
        std::type_index key(typeid(Play_GameState));
        return key;
    }

    return getTypeId();
}
