#include "../includes/GameOverState.hpp"


GameOverState::GameOverState(): MenuState("GAME OVER", {"Retry", "Main Menu", "Quit"}) {};

void GameOverState::processEnter(sf::RenderWindow &window, State **self)
{
    switch(selected)
    {
        case 0:
            *self = gameState;
            (*self)->init(window);
            break;
        case 1:
            *self = mainMenuState;
            (*self)->init(window);
            break;
        case 2:
            exit(0);
            break;
        default:
            break;
    }
}

State *gameOverState = new GameOverState();
