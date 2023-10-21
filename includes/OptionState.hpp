#ifndef OPTIONSTATE_H
#define OPTIONSTATE_H

#include "State.hpp"
#include "MenuState.hpp"
#include "StateDef.hpp"

class OptionState: public MenuState
{
    protected:
        std::array<sf::Text,3> difficulty_names;
        virtual void processEnter(sf::RenderWindow &window, State **self);
        virtual void difficultyUp();
        virtual void difficultyDown();
        virtual void computeDifficultyPos();

    public:
        OptionState();
        virtual void processEvent(sf::RenderWindow &window, State **self, sf::Event event);
        virtual void init(sf::RenderWindow &window);
        virtual void draw(sf::RenderWindow &window) const;
};

#endif
