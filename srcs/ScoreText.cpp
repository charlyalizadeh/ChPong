#include "../includes/ScoreText.hpp"

ScoreText::ScoreText(): scores({0, 0}) { };

void ScoreText::init(std::array<int,2> scores, const sf::Font& font)
{
    scoresText = std::vector<sf::Text>(2);
    for(size_t i = 0; i < 2; i++)
    {
        if(scores[i] < 10)
            scoresText[i].setString("0" + std::to_string(scores[i]));
        else
            scoresText[i].setString(std::to_string(scores[i]));
        scoresText[i].setFont(font);
        scoresText[i].setCharacterSize(64);
        scoresText[i].setFillColor(sf::Color::White);
    }
}

void ScoreText::computePos(sf::Vector2u winSize)
{
    auto scoresText1Bounds = scoresText[0].getGlobalBounds();
    auto scoresText2Bounds = scoresText[1].getGlobalBounds();
    scoresText[0].setPosition(sf::Vector2f(winSize.x / 2.f - scoresText1Bounds.width - 20, 5));
    scoresText[1].setPosition(sf::Vector2f(winSize.x / 2.f + 20, 5));

}

void ScoreText::increase_score(int player)
{
    if(player != 0 && player != 1)
        return;
    scores[player]++;
    if(scores[player] < 10)
        scoresText[player].setString("0" + std::to_string(scores[player]));
    else
        scoresText[player].setString(std::to_string(scores[player]));
}

const sf::Text& ScoreText::getText(int i) const
{
    return scoresText[i];
}
