#include "Gamemodes_state.h"

#include <string>
#include <map>
#include <iostream>

using namespace sf;

Gamemodes_state::Gamemodes_state()
: selected_option{0}
{
    background_image.loadFromFile("spelplan.png");
    font.loadFromFile("Roboto-Regular.ttf");
    settings = sh.load();
}

std::string Gamemodes_state::get_key(int index)
{
    int tmp{0};
    std::string key;
    for (std::pair<std::string, int> s : settings)
    {
        key = s.first;
        if (tmp == index)
        {
            break;
        }
        
        ++tmp;
    }

    return key;
}

int Gamemodes_state::change_value(std::string key)
{
    if (key == "Window width" || key == "Window height")
    {
        return 0;
    }
    else if (key == "Ball size" || key == "Ball velocity" || 
             key == "Worm velocity" || key == "Extra length per food")
    {
        return 5;
    }
    else if (key == "Worm segments")
    {
        return 10;
    }
    else if (key == "Milliseconds between worm segment decay")
    {
        return 50;
    }
    else
    {
        return 1;
    }
}

void Gamemodes_state::process_event(Game_engine* game, Event const& event)
{
    if (event.type == Event::KeyPressed)
    {
        if ((event.key.code == Keyboard::W || event.key.code == Keyboard::Up) 
             && selected_option > 0)
        {
            --selected_option;
        }
        else if ((event.key.code == Keyboard::S || event.key.code == Keyboard::Down) 
                  && selected_option < settings.size() - 1)
        {
            ++selected_option;
        }
        else if (event.key.code == Keyboard::A || event.key.code == Keyboard::Left)
        {
            std::string key{get_key(selected_option)};

            if (settings.at(key) - change_value(key) >= 0)
            {
                settings.at(key) -= change_value(key);
            }
        }
        else if (event.key.code == Keyboard::D || event.key.code == Keyboard::Right)
        {
            std::string key{get_key(selected_option)};
            settings.at(key) += change_value(key);
        }
        else if (event.key.code == Keyboard::Q)
        {
            Settings_handler template_sh{"template_settings.txt"};
            sh.write(template_sh.load());
            settings = sh.load();
        }
        else if (event.key.code == Keyboard::Escape)
        {
            sh.write(settings);
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
    reset_btn.setOrigin(rect.left,
                     rect.top  + rect.height / 2);
    window.draw(reset_btn);

    Text exit_btn;
    exit_btn.setFont(font);
    exit_btn.setCharacterSize(20);
    exit_btn.setString("Press 'Esc' to save and exit");
    exit_btn.setPosition(window.getSize().x - 300, window.getSize().y - 50);
    rect = exit_btn.getLocalBounds();
    exit_btn.setOrigin(rect.left,
                     rect.top  + rect.height / 2);
    window.draw(exit_btn);

    unsigned int tmp_x{75};
    unsigned int tmp_y{65};
    unsigned int index{0};
    for (std::pair<std::string, int> s : settings)
    {
        if (index == selected_option)
        {
            CircleShape dot;
            dot.setFillColor(Color::Red);
            dot.setRadius(4);
            dot.setPosition(tmp_x - 15, tmp_y);
            rect = dot.getLocalBounds();
            dot.setOrigin(rect.left + rect.width / 2,
                          rect.top  + rect.height / 2);
            window.draw(dot);
        }

        Text option;
        option.setFont(font);
        option.setCharacterSize(20);
        option.setString(s.first + ": " + std::to_string(s.second));
        option.setPosition(tmp_x, tmp_y);
        rect = option.getLocalBounds();
            option.setOrigin(rect.left,
                             rect.top  + rect.height / 2);
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