#include "../includes/MenuState.hpp"

MenuState::MenuState(const std::string &title, const std::vector<std::string> &choices) {
    this->title = sf::Text();
    this->title.setString(title);
    this->title.setFont(font);
    this->title.setCharacterSize(128);
    this->title.setFillColor(sf::Color::White);
    this->choices = std::vector<sf::Text>(choices.size());
    for(size_t i = 0; i < choices.size(); i++)
    {
        this->choices[i] = sf::Text();
        this->choices[i].setString(choices[i]);
        this->choices[i].setFont(font);
        this->choices[i].setCharacterSize(64);
        this->choices[i].setFillColor(sf::Color::White);
    }
    selected = 0;
    gapSize = 20;
};

sf::Vector2u MenuState::getMenuSize()
{
    int x = 0, y = 0;
    for(size_t i = 0; i < choices.size(); i++)
    {
        auto bounds = choices[i].getLocalBounds();
        y += bounds.height + gapSize;
        if(bounds.width > x)
            x = bounds.width;
    }
    return sf::Vector2u(x, y);
}

void MenuState::computeOrigin(const sf::RenderWindow& window)
{
    auto winSize = window.getSize();
    auto menuSize = getMenuSize();
    origin.x = winSize.x / 2.0f - menuSize.x / 2.0f;
    origin.y = winSize.y / 2.0f - menuSize.y / 2.0f;
}

void MenuState::computeChoicesPos(const sf::RenderWindow &window)
{
    auto winSize = window.getSize();
    float y = origin.y;
    auto titleBounds = title.getLocalBounds();
    title.setPosition({
            winSize.x / 2.0f - titleBounds.width / 2.0f,
            y - 128 - gapSize * 2
    });
    for(size_t i = 0; i < choices.size(); i++)
    {
        auto bounds = choices[i].getLocalBounds();
        choices[i].setPosition({
                winSize.x / 2.0f - bounds.width / 2.0f,
                y
        });
        y += bounds.height + gapSize;
    }
}

void MenuState::menuUp()
{
    selected--;
    if(selected < 0)
        selected = choices.size() - 1;
}

void MenuState::menuDown()
{
    selected++;
    if(selected > choices.size() - 1)
        selected = 0;
}

void MenuState::processEnter(sf::RenderWindow &window, State **self) {}

void MenuState::init(sf::RenderWindow &window) {
    selected = 0;
    computeOrigin(window);
    computeChoicesPos(window);
}

void MenuState::setChoicesStyle()
{
    for(size_t i = 0; i < choices.size(); i++)
    {
        if(i == (size_t)selected)
            choices[i].setStyle(sf::Text::Bold | sf::Text::Underlined);
        else
            choices[i].setStyle(sf::Text::Regular);
    }
}

void MenuState::update(sf::RenderWindow &window, State **self) {
    sf::Event event;
    while (window.pollEvent(event))
        processEvent(window, self, event);
    setChoicesStyle();
}

void MenuState::processEvent(sf::RenderWindow &window, State **self, sf::Event event)
{
    if (event.type == sf::Event::Closed)
        window.close();
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::Down:
                menuDown();
                break;
            case sf::Keyboard::Up:
                menuUp();
                break;
            case sf::Keyboard::Enter:
                processEnter(window, self);
                break;
            default:
                break;
        }
    }
}

void MenuState::draw(sf::RenderWindow &window) const
{
    window.clear(sf::Color::Black);
    window.draw(title);
    for(size_t i = 0; i < choices.size(); i++)
        window.draw(choices[i]);
    window.display();
};
