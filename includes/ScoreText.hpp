#ifndef SCORETEXT_H
#define SCORETEXT_H

#include <array>
#include <SFML/Graphics.hpp>

class ScoreText
{
    private:
        std::array<int,2> scores;

    public:
        std::vector<sf::Text> scoresText;
        ScoreText();
        void init(std::array<int,2> scores, const sf::Font& font);
        void computePos(sf::Vector2u winSize);
        void increase_score(int player);
        const sf::Text& getText(int i) const;
};

#endif
