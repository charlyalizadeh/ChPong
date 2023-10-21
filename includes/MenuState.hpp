#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.hpp"
#include "StateDef.hpp"
#include <array>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdio.h>

class MenuState: public State
{
    protected:
        int selected;
        sf::Text title;
        std::vector<sf::Text> choices;
        int gapSize;
        sf::Vector2f origin;

    protected:
        virtual sf::Vector2u getMenuSize();
        virtual void computeOrigin(const sf::RenderWindow& window);
        virtual void computeChoicesPos(const sf::RenderWindow &window);
        virtual void menuUp();
        virtual void menuDown();
        virtual void processEnter(sf::RenderWindow &window, State **self);
        virtual void setChoicesStyle();

    public:
        MenuState(const std::string &title, const std::vector<std::string> &choices);
        virtual void init(sf::RenderWindow &window);
        virtual void update(sf::RenderWindow &window, State **self);
        virtual void processEvent(sf::RenderWindow &window, State **self, sf::Event event);
        virtual void draw(sf::RenderWindow &window) const;
};

#endif
