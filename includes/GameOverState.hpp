#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "MenuState.hpp"
#include "StateDef.hpp"

class GameOverState: public MenuState
{
    protected:
        virtual void processEnter(sf::RenderWindow &window, State **self);

    public:
        GameOverState();
};

#endif
