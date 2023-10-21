#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "MenuState.hpp"
#include "StateDef.hpp"

class MainMenuState: public MenuState
{
    private:
        void processEnter(sf::RenderWindow &window, State **self);

    public:
        MainMenuState();
};

#endif
