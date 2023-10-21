#ifndef PONGBAR_H
#define PONGBAR_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

enum class Move {
    NONE,
    DOWN,
    UP
};

struct PongBar {
        sf::Vector2f origin;
        sf::Vector2f dims;
        int speed;
        sf::RectangleShape rect;
        Move move;

        PongBar(
            sf::Vector2f origin={0.f, 0.f},
            sf::Vector2f dims={15.f, 90.f},
            int speed=700
        );

        void goDown(const sf::Vector2u &winSize, float fElapsedTime);
        void goUp(const sf::Vector2u &winSize, float fElapsedTime);
        void goTo(const sf::Vector2u &winSize, float y);
        void update(const sf::RenderWindow &window, float fElapsedTime);
};

bool check_rect_intersect(
    sf::Vector2f origin1, sf::Vector2f dims1,
    sf::Vector2f origin2, sf::Vector2f dims2
);

sf::Vector2f get_intersect(
        sf::Vector2f p1, sf::Vector2f p2,
        sf::Vector2f p3, sf::Vector2f p4
);

#endif
