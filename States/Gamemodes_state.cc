#include "Gamemodes_state.h"

#include "../Framework/Settings_handler.h"
#include <string>
#include <map>
#include <iostream>

using namespace sf;

Gamemodes_state::Gamemodes_state()
: selected_option{0}
{
    background_image.loadFromFile("spelplan.png");
    font.loadFromFile("Roboto-Regular.ttf");
}

std::string Gamemodes_state::get_setting_at_index(int index)
{
    int counter{0};
    std::string setting;
    for (std::pair<std::string, int> s : Settings_handler::get_settings())
    {
        setting = s.first;
        if (counter == index)
        {
            break;
        }
        
        ++counter;
    }

    return setting;
}

void Gamemodes_state::process_event(Game_engine* game, Event const& event)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up)
        {
            if (selected_option > 0)
            {
                --selected_option;
            }
        }
        else if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down)
        {
            if (selected_option < Settings_handler::get_settings().size() - 1)
            {
                ++selected_option;
            }
        }
        else if (event.key.code == Keyboard::A || event.key.code == Keyboard::Left)
        {
            std::string setting{get_setting_at_index(selected_option)};
            Settings_handler::dec_setting(setting);
        }
        else if (event.key.code == Keyboard::D || event.key.code == Keyboard::Right)
        {
            std::string setting{get_setting_at_index(selected_option)};
            Settings_handler::inc_setting(setting);
        }
        else if (event.key.code == Keyboard::Q)
        {
            Settings_handler::load_default();
        }
        else if (event.key.code == Keyboard::Escape)
        {
            Settings_handler::write();
            game -> exit_current_state = true;
        }
    }
}

void Gamemodes_state::update(Game_engine* game, Time const& delta)
{}

void Gamemodes_state::draw(RenderWindow& window)
{
    window.clear();
    
    RectangleShape background;
    background.setSize(Vector2f(window.getSize()));
    background.setTexture(&background_image);
    window.draw(background);

    Text reset_btn;
    reset_btn.setFont(font);
    reset_btn.setCharacterSize(20);
    reset_btn.setString("Press 'Q' for default settings");
    reset_btn.setPosition(window.getSize().x - 310, window.getSize().y - 100);
    FloatRect rect = reset_btn.getLocalBounds();
    reset_btn.setOrigin(rect.left, rect.top  + rect.height / 2);
    window.draw(reset_btn);

    Text exit_btn;
    exit_btn.setFont(font);
    exit_btn.setCharacterSize(20);
    exit_btn.setString("Press 'Esc' to save and exit");
    exit_btn.setPosition(window.getSize().x - 300, window.getSize().y - 50);
    rect = exit_btn.getLocalBounds();
    exit_btn.setOrigin(rect.left, rect.top  + rect.height / 2);
    window.draw(exit_btn);

    unsigned int tmp_x{75};
    unsigned int tmp_y{65};
    unsigned int index{0};
    for (std::pair<std::string, int> s : Settings_handler::get_settings())
    {
        if (index == selected_option)
        {
            CircleShape dot;
            dot.setFillColor(Color::Red);
            dot.setRadius(4);
            dot.setPosition(tmp_x - 15, tmp_y);
            rect = dot.getLocalBounds();
            dot.setOrigin(rect.left + rect.width / 2, rect.top  + rect.height / 2);
            window.draw(dot);
        }

        Text option;
        option.setFont(font);
        option.setCharacterSize(20);
        option.setString(s.first + ": " + std::to_string(s.second));
        option.setPosition(tmp_x, tmp_y);
        rect = option.getLocalBounds();
            option.setOrigin(rect.left, rect.top  + rect.height / 2);
        window.draw(option);

        ++index;
        tmp_y += 50;

        if (tmp_y > window.getSize().y - 100)
        {
            tmp_x += 500;
            tmp_y = 65;
        }
    }

    window.display();
}