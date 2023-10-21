#include "../includes/GameState.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

GameState::GameState() { };


void GameState::processKeyPressed(sf::RenderWindow &window, State **self, sf::Keyboard::Key key)
{
    switch(key)
    {
        case sf::Keyboard::Down:
            player.move = Move::DOWN;
            break;
        case sf::Keyboard::Up:
            player.move = Move::UP;
            break;
        case sf::Keyboard::Escape:
            *self = mainMenuState;
            (*self)->init(window);
            break;
        default:
            break;
    }
}

void GameState::init(sf::RenderWindow &window)
{
    auto winSize = window.getSize();
    player = PongBar({10.f, winSize.y / 2.f - 40.f});
    ai = PongBar({winSize.x - 25.f, winSize.y / 2.f - 40.f});
    ball = Ball({winSize.x / 2.f, winSize.y / 4.f}, {400.f * (difficulty + 1), 100.f * (difficulty + 1)});
    clock = sf::Clock();
    float gapSize = (winSize.y + 15.f) / 30.f - 15.f;
    middleBar = std::vector<sf::RectangleShape>(30);
    float y = 0;
    for(size_t i = 0; i < middleBar.size(); i++)
    {
        middleBar[i] = sf::RectangleShape({15.f, 15.f});
        middleBar[i].setFillColor(sf::Color::White);
        middleBar[i].setPosition({winSize.x / 2.f - 7.5f, y});
        y += 15.f + gapSize;
    }
    scoreText = ScoreText();
    scoreText.init({0, 0}, font);
    scoreText.computePos(winSize);
}

void GameState::update(sf::RenderWindow &window, State **self)
{
    sf::Time elapsed = clock.restart();
    float fElapsedTime = elapsed.asSeconds();
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if(event.type == sf::Event::KeyPressed)
            processKeyPressed(window, self, event.key.code);
        if(event.type == sf::Event::KeyReleased)
            if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
                player.move = Move::NONE;
    }
    if(ball.origin.x <= 0 || ball.origin.x + ball.dims.x >= window.getSize().x)
    {
        *self = gameOverState;
        (*self)->init(window);
    }
    player.update(window, fElapsedTime);
    ai.update(window, fElapsedTime);
    if(check_rect_intersect(ball.origin, ball.dims, player.origin, player.dims))
        scoreText.increase_score(0);
    if(check_rect_intersect(ball.origin, ball.dims, ai.origin, ai.dims))
        scoreText.increase_score(1);
    ball.update(window, fElapsedTime, player, ai);
    ai.origin.y = ball.origin.y - ai.dims.y / 2.f;
}

void GameState::draw(sf::RenderWindow &window) const
{
    window.clear(sf::Color::Black);
    window.draw(player.rect);
    window.draw(ai.rect);
    window.draw(ball.rect);
    for(size_t i = 0; i < middleBar.size(); i++)
        window.draw(middleBar[i]);
    window.draw(scoreText.scoresText[0]);
    window.draw(scoreText.scoresText[1]);
    window.display();
}

void GameState::set_difficulty(int newDifficulty)
{
    if(newDifficulty <= 0 || newDifficulty > 3)
        return;
    difficulty = newDifficulty;
}

State *gameState = new GameState();
