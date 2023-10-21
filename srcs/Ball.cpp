#include "../includes/Ball.hpp"


Ball::Ball(
        sf::Vector2f origin,
        sf::Vector2f acc,
        sf::Vector2f dims
): origin(origin), acc(acc), dims(dims)
{
    rect = sf::RectangleShape(dims);
    rect.setFillColor(sf::Color::White);
}

void Ball::fix_top(int y)
{
    if(origin.y >= y)
        return;
    sf::Vector2f temp_acc = -acc / (float)fabs(acc.y);
    temp_acc *= (float)fabs(y - origin.y);
    origin += temp_acc;
}

void Ball::fix_bottom(int y)
{
    if(origin.y + dims.y < y)
        return;
    sf::Vector2f temp_acc = -acc / (float)fabs(acc.y);
    temp_acc *= (float)fabs(origin.y + dims.y - y);
    origin += temp_acc;
}

void Ball::fix_right(int x)
{
    if(origin.x + dims.x < x)
        return;
    sf::Vector2f temp_acc = -acc / (float)fabs(acc.x);
    temp_acc *= (float)fabs(origin.x + dims.x - x);
    origin += temp_acc;
}

void Ball::fix_left(int x)
{
    if(origin.x >= x)
        return;
    sf::Vector2f temp_acc = -acc / (float)fabs(acc.x);
    temp_acc *= (float)fabs(x - origin.x);
    origin += temp_acc;
}

void ball_intersect_bar(Ball &ball, const PongBar &bar, bool left)
{
    if(!check_rect_intersect(ball.origin, ball.dims, bar.origin, bar.dims))
        return;
    if(left)
        ball.fix_left(bar.origin.x + bar.dims.x);
    else
        ball.fix_right(bar.origin.x);
    int middle_bar = bar.origin.y + bar.dims.y / 2;
    int middle_ball = ball.origin.y + ball.dims.y / 2;
    float magn = sqrt(ball.acc.x * ball.acc.x + ball.acc.y * ball.acc.y);
    float val = (float)sqrt(0.5f);
    int sign = ball.acc.x < 0 ? 1 : -1;
    if(middle_ball < middle_bar)
        ball.acc = {sign * magn * val, -magn * val};
    else if(middle_ball > middle_bar)
        ball.acc = {sign * magn * val, magn * val};
    else
        ball.acc = {sign * magn, 0};
}

bool Ball::update(
   const sf::RenderWindow &window,
   float fElapsedTime,
   const PongBar &player,
   const PongBar& ai
)
{
    origin += acc * fElapsedTime;
    rect.setPosition(origin);
    if(origin.y < 0)
    {
        fix_top(0);
        acc.y = -acc.y;
    }
    else if(origin.y + dims.y > window.getSize().y)
    {
        fix_bottom(window.getSize().y);
        acc.y = -acc.y;
    }
    ball_intersect_bar(*this, player, true);
    ball_intersect_bar(*this, ai, false);
    return check_rect_intersect(origin, dims, player.origin, player.dims);
}

sf::Vector2f get_ball_intersect_bar(
    const Ball& ball,
    const sf::RenderWindow &window,
    const PongBar &player,
    const PongBar& ai
)
{
    Ball ball_copy = ball;
    while(ball_copy.origin.y != ai.origin.y)
        ball_copy.update(window, 0.1f, player, ai);
    return ball_copy.origin;
}
