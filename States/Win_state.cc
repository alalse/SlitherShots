#include "Win_state.h"
#include <iostream>

using namespace sf;

Win_state::Win_state(std::string w): winner{w} 
{
    font.loadFromFile("Roboto-Regular.ttf");
    background_image.loadFromFile("spelplan.png");
}

void Win_state::process_event(Game_engine* game, Event const& event)
{        
    switch (event.type)
    {
    case Event::Closed:
        break;
    case Event::KeyPressed:
        if (event.key.code == Keyboard::Escape)
        {
            game -> pop_state();
            game -> pop_state();
        }
    default:
        break;
    }
}
void Win_state::update(Game_engine* game, sf::Time const& delta)
{}

void Win_state::draw(sf::RenderWindow& window)
{
    RectangleShape background;
    background.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    background.setSize(Vector2f(400, 200));
    FloatRect rect = background.getLocalBounds();
    background.setOrigin(rect.left + rect.width / 2,
                         rect.top  + rect.height / 2);
    background.setTexture(&background_image);
    window.draw(background);

    Text title{winner + " Wins!", font, 40};
    title.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 50);
    rect = title.getLocalBounds();
    title.setOrigin(rect.left + rect.width / 2,
                    rect.top  + rect.height / 2);
    window.draw(title);

    Text exit{"Press 'Esc' to return to main menu...", font, 20};
    exit.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    rect = exit.getLocalBounds();
    exit.setOrigin(rect.left + rect.width / 2,
                   rect.top  + rect.height / 2);
    window.draw(exit);

    window.display();
}