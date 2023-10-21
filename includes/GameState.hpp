#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.hpp"
#include "StateDef.hpp"
#include "PongBar.hpp"
#include "Ball.hpp"
#include "ScoreText.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class GameState: public State
{
    private:
        PongBar player, ai;
        Ball ball;
        ScoreText scoreText;
        sf::Clock clock;
        std::vector<sf::RectangleShape> middleBar;

        void processKeyPressed(sf::RenderWindow &window, State **self, sf::Keyboard::Key key);
    public:
        GameState();
        void init(sf::RenderWindow &window);
        void update(sf::RenderWindow &window, State **self);
        void draw(sf::RenderWindow &window) const;
        void set_difficulty(int newDifficulty);
};

#endif
