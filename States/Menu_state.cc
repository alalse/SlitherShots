#include "Menu_state.h"
#include "Play_state.h"
#include "Help_state.h"
#include "Gamemodes_state.h"
#include <iostream>

using namespace sf;

Menu_state::Menu_state()
: selected_menu{0}
{
    background_image.loadFromFile("spelplan.png");
    font.loadFromFile("Roboto-Regular.ttf");

    menu_items.push_back(new Text{"Play", font});
    menu_items.push_back(new Text{"Gamemodes", font});
    menu_items.push_back(new Text{"Help", font});
    menu_items.push_back(new Text{"Exit", font});
}

Menu_state::~Menu_state()
{
    for (Text* t : menu_items)
    {
        delete t;
    }
}

void Menu_state::process_event(Game_engine* game, Event const& event)
{
    switch (event.type)
    {
    case Event::Closed:
        break;

    case Event::KeyPressed:
        switch (event.key.code)
        {
        case ::Keyboard::W:
        case ::Keyboard::Up:
            if (selected_menu > 0 && selected_menu <= 3)
            {
                --selected_menu;
            }
            break;

        case ::Keyboard::S:
        case ::Keyboard::Down:
            if (selected_menu >= 0 && selected_menu < 3)
            {
                ++selected_menu;
            }
            break;

        case ::Keyboard::Return:
            if (selected_menu == 0) 
            { 
                game -> push_state(new Play_state()); 
            }
            else if (selected_menu == 1)
            {
                game -> push_state(new Gamemodes_state());
            }
            else if (selected_menu == 2)
            {
                game -> push_state(new Help_state());
            }
            else
            {
                game -> running = false;
            }
            
            break;
        
        default:
            break;
        }
    
    default:
        break;
    }
}

void Menu_state::update(Game_engine* game, Time const& delta)
{}

void Menu_state::draw(RenderWindow& window)
{
    RectangleShape background;
    background.setSize(Vector2f(window.getSize()));
    background.setTexture(&background_image);
    window.draw(background);

    Text game_title;
    game_title.setString("SlitherShots!");
    game_title.setFillColor(Color::White);
    game_title.setCharacterSize(60);
    game_title.setFont(font);
    FloatRect rect = game_title.getLocalBounds();
    game_title.setOrigin(rect.left + rect.width / 2,
                         rect.top  + rect.height / 2);
    game_title.setPosition(Vector2f(window.getSize().x / 2, 100));
    window.draw(game_title);

    int index = 0;
    int y_cord = 200;
    for (Text* t : menu_items)
    {
        if (index == selected_menu)
        {
            t -> setFillColor(Color::White);
        }
        else
        {
            t -> setFillColor(Color::Red);
        }

        y_cord += 100;
        FloatRect tmp = t -> getLocalBounds();
        t -> setOrigin(tmp.left + tmp.width / 2,
                       tmp.top  + tmp.height / 2);
        t -> setPosition(window.getSize().x / 2, y_cord);
        t -> setCharacterSize(35);
        window.draw(*t);
        ++index;
    }

    window.display();
}
