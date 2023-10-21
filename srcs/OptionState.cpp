#include "../includes/OptionState.hpp"

OptionState::OptionState(): MenuState("Option", {"Difficulty", "Return"})
{
    difficulty_names = std::array<sf::Text,3>();
    difficulty_names[0].setString("Easy");
    difficulty_names[0].setFillColor(sf::Color(50, 205, 50));
    difficulty_names[1].setString("Medium");
    difficulty_names[1].setFillColor(sf::Color(255, 165, 0));
    difficulty_names[2].setString("Hard");
    difficulty_names[2].setFillColor(sf::Color(220, 20, 60));
    for(size_t i = 0; i < difficulty_names.size(); i++)
    {
        difficulty_names[i].setFont(font);
        difficulty_names[i].setCharacterSize(64);
    }
};

void OptionState::difficultyUp()
{
    difficulty++;
    if(difficulty > difficulty_names.size() - 1)
        difficulty = 0;
}

void OptionState::difficultyDown()
{
    difficulty--;
    if(difficulty < 0)
        difficulty = difficulty_names.size() - 1;
}

void OptionState::computeDifficultyPos()
{
    auto diffChoiceBounds = choices[0].getGlobalBounds();
    auto diffChoicePos = choices[0].getPosition();
    for(size_t i = 0; i < difficulty_names.size(); i++)
    {
        difficulty_names[i].setPosition({
                diffChoicePos.x + diffChoiceBounds.width + 50,
                diffChoicePos.y
        });
    }
}

void OptionState::processEnter(sf::RenderWindow &window, State **self)
{
    switch(selected)
    {
        case 0:
            break;
        case 1:
            *self = mainMenuState;
            (*self)->init(window);
            break;
        default:
            break;
    }
}

void OptionState::processEvent(sf::RenderWindow &window, State **self, sf::Event event)
{
    MenuState::processEvent(window, self, event);
    if(event.type == sf::Event::KeyPressed && selected == 0)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::Left:
                difficultyDown();
                break;
            case sf::Keyboard::Right:
                difficultyUp();
                break;
            default:
                break;
        }
    }
}

void OptionState::init(sf::RenderWindow &window)
{
    MenuState::init(window);
    computeDifficultyPos();
}

void OptionState::draw(sf::RenderWindow &window) const
{
    window.clear(sf::Color::Black);
    window.draw(title);
    for(size_t i = 0; i < choices.size(); i++)
        window.draw(choices[i]);
    window.draw(difficulty_names[difficulty]);
    window.display();
}

State *optionState = new OptionState();
