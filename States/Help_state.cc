#include "Help_state.h"
#include <iostream>

using namespace sf;

Help_state::Help_state()
: current_slide{0} 
{  
    Texture t;
    t.loadFromFile("help1.png");
    slides.push_back(t);
}

void Help_state::process_event(Game_engine* game, Event const& event)
{
    if (event.type == Event::KeyPressed && !slides.empty())
    {
        slides.erase(slides.begin());
    }
}

void Help_state::update(Game_engine* game, Time const& delta)
{
    if (slides.empty())
    {
        game -> exit_current_state = true;
    }
}

void Help_state::draw(RenderWindow& window)
{
    RectangleShape help_box;
    help_box.setSize(Vector2f(750, 475));
    FloatRect rect = help_box.getLocalBounds();
    help_box.setOrigin(rect.left + rect.width / 2,
                         rect.top  + rect.height / 2);

    help_box.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    help_box.setTexture(&slides.front());
    window.draw(help_box);

    window.display();
}