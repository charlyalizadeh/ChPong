#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

class State
{
    protected:
        static int difficulty;

    public:
        static sf::Font font;
        State();
        virtual void init(sf::RenderWindow &window);
        virtual void update(sf::RenderWindow &window, State **self);
        virtual void draw(sf::RenderWindow &window) const;
};

#endif
