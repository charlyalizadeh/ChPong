#include "../includes/State.hpp"

State::State() {
};

int State::difficulty = 0;

sf::Font State::font = sf::Font();

void State::init(sf::RenderWindow &window) {};

void State::update(sf::RenderWindow &window, State **self) {};

void State::draw(sf::RenderWindow &window) const {};
