#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "PongBar.hpp"

struct Ball
{
    sf::Vector2f origin;
    sf::Vector2f acc;
    sf::Vector2f dims;
    sf::RectangleShape rect;

    Ball(
        sf::Vector2f origin={0.f, 0.f},
        sf::Vector2f acc={20.f, 20.f},
        sf::Vector2f dims={15.f, 15.f}
    );
    void fix_top(int y);
    void fix_bottom(int y);
    void fix_right(int x);
    void fix_left(int x);
    bool update(
        const sf::RenderWindow &window,
        float fElapsedTime,
        const PongBar &bar1,
        const PongBar& bar2
    );
};

void ball_intersect_bar(Ball &ball, const PongBar &bar, bool left);
sf::Vector2f get_ball_intersect_bar(
    const Ball& ball,
    const sf::RenderWindow &window,
    const PongBar &player,
    const PongBar& ai
);

#endif
