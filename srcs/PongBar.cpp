#include "../includes/PongBar.hpp"
#include <SFML/System/Vector2.hpp>

PongBar::PongBar(sf::Vector2f origin, sf::Vector2f dims, int speed): origin(origin), dims(dims), speed(speed) {
    rect = sf::RectangleShape(dims);
    rect.setFillColor(sf::Color::White);
};

void PongBar::update(const sf::RenderWindow &window, float fElapsedTime)
{
    auto winSize = window.getSize();
    if(move == Move::UP)
        goUp(winSize, fElapsedTime);
    else if(move == Move::DOWN)
        goDown(winSize, fElapsedTime);
    rect.setPosition(origin);
}

void PongBar::goDown(const sf::Vector2u &winSize, float fElapsedTime)
{
    if(origin.y + dims.y < winSize.y)
    {
        origin.y += speed * fElapsedTime;
        if(origin.y + dims.y > winSize.y)
            origin.y = winSize.y - dims.y;
    }
}

void PongBar::goUp(const sf::Vector2u &winSize, float fElapsedTime)
{
    if(origin.y > 0)
    {
        origin.y -= speed * fElapsedTime;
        if(origin.y < 0)
            origin.y = 0;
    }
}

void PongBar::goTo(const sf::Vector2u &winSize, float y)
{
    if(y >= 0 && y < winSize.y)
        origin.y = y;
}

bool check_rect_intersect(
    sf::Vector2f origin1, sf::Vector2f dims1,
    sf::Vector2f origin2, sf::Vector2f dims2)
{
    sf::Vector2f limit_rect1 = {origin1.x + dims1.x, origin1.y + dims1.y};
    sf::Vector2f limit_rect2 = {origin2.x + dims2.x, origin2.y + dims2.y};
    bool is_in_x = (limit_rect1.x >= origin2.x && limit_rect1.x <= limit_rect2.x)
        || (origin1.x >= origin2.x && origin1.x <= limit_rect2.x);
    bool is_in_y = (limit_rect1.y >= origin2.y && limit_rect1.y <= limit_rect2.y)
        || (origin1.y >= origin2.y && origin1.y <= limit_rect2.y);
    return is_in_x && is_in_y;
}

sf::Vector2f get_intersect(
        sf::Vector2f p1, sf::Vector2f p2,
        sf::Vector2f p3, sf::Vector2f p4
)
{
    float den = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
    float num1 = (p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x);
    float num2 = (p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x);
    return {num1 / den, num2 / den};
}
