#include "../includes/State.hpp"
#include "../includes/StateDef.hpp"
#include "../includes/GameState.hpp"
#include "../includes/MainMenuState.hpp"

#include <stdio.h>

int main() {
    State *state;
    if(!state->font.loadFromFile("fonts/ARCADECLASSIC.TTF"))
        exit(1);
    state->font.setSmooth(false);
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML");
    state = mainMenuState;
    state->init(window);
    while(window.isOpen())
    {
        state->draw(window);
        window.display();
        state->update(window, &state);
    }
    delete gameState;
    delete mainMenuState;
    delete gameOverState;
    delete optionState;
    return 0;
}
