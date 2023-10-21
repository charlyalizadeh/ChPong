#include "../includes/MainMenuState.hpp"


MainMenuState::MainMenuState(): MenuState("ChPong", {"Play", "Options", "Scores", "Quit"}) {};

void MainMenuState::processEnter(sf::RenderWindow &window, State **self)
{
    switch(selected)
    {
        case 0:
            *self = gameState;
            (*self)->init(window);
            break;
        case 1:
            *self = optionState;
            (*self)->init(window);
            break;
        case 3:
            exit(0);
            break;
        default:
            break;
    }
}

State *mainMenuState = new MainMenuState();
