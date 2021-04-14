#include "Worm.h"
#include "Worm_segment.h"
#include "Wall.h"
#include "Goal.h"
#include "Line.h"
#include "../Food/Food.h"
#include "../Framework/Settings_handler.h"

#include <string>
#include <iostream>
#include <map>
#include <cmath>
#include <memory>

using namespace sf;

Worm::Worm(std::string name)
: Movable_object{0, 0, 0, 0}, has_scored{false},
  name{name}, body{nullptr}, rotation_per_tick{0.1}, score{0}, food_boost{false}
  { 
    Settings_handler sh;
    settings = sh.load();

    velocity = settings.at("Worm velocity");
    width = settings.at("Worm width") / 2;
    height = settings.at("Worm width") / 2;
    segments_per_food = settings.at("Extra length per food");
    base_segment_count = settings.at("Worm segments");
    decay_tick = settings.at("Milliseconds between worm segment decay");
    decay_timer = Clock();
    boost_duration = Clock();
    
    if (name == "Player 1")
    {
        x = 100;
        y = 350;
        rotation = 0;
        keys = {{Keyboard::Key::A, false}, {Keyboard::Key::D, false}};
    }
    else if (name == "Player 2")
    {
        x = settings.at("Window width") - 100;
        y = 350;
        rotation = M_PI;
        keys = {{Keyboard::Key::Left, false},{Keyboard::Key::Right, false}};
    }

    upper_body_connector = std::make_shared<Vector2f>(Vector2f(x, y-width));
    lower_body_connector = std::make_shared<Vector2f>(Vector2f(x, y+width));
    body = std::make_shared<Worm_segment>(Worm_segment(upper_body_connector, 
                                          lower_body_connector)); 

    add_segments(base_segment_count);
}

void Worm::add_segments(int const amount)
{
    body -> add_segments(amount);
}

void Worm::process_keypress(Keyboard::Key const& key)
{
    if (keys.find(key) != keys.end())
    {
        keys.at(key) = !keys.at(key);
    }
}

void Worm::collide(Game_object* obj)
{
    if (dynamic_cast<Wall*>(obj))
    {
        if (rotation <= M_PI + (M_PI / 2) && rotation > (M_PI / 2))
        {
            if (rotation <= M_PI + (M_PI / 2) && rotation > M_PI)
            {
                y = 20;
            }
            else
            {
                y = settings.at("Window height") - height - 20;
            }
            
            rotation = M_PI;
        }
        else
        {
            if (rotation <= (M_PI / 2) && rotation > 0)
            {
                y = settings.at("Window height") - height - 20;
            }
            else
            {
                y = 20;
            }

            rotation = 0;
        }
    }
    if (dynamic_cast<Line*>(obj))
    {
        if (rotation <= M_PI + (M_PI / 2) && rotation > (M_PI / 2))
        {   
            x = (settings.at("Window width") / 2) + width + 25;
        }
        else
        {
            x = (settings.at("Window width") / 2) - width - 25;
        }

        if (rotation <= M_PI && rotation > 0)
        {   
            rotation = M_PI / 2;
        }
        else
        {
            rotation = M_PI + (M_PI / 2);
        }
    }
    else if (dynamic_cast<Goal*>(obj))
    {
        if (rotation <= M_PI && rotation > 0)
        {
            if (rotation <= (M_PI / 2) && rotation > 0)
            {
                x = settings.at("Window width") - width - 20;
            }
            else
            {
                x = 20;
            }

            rotation = M_PI / 2;
        }
        else
        {
            if (rotation <= M_PI + (M_PI / 2) && rotation > M_PI)
            {
                x = 20;
            }
            else
            {
                x = settings.at("Window width") - width - 20;
            }

            rotation = M_PI + (M_PI / 2);
        }
    }
    else if (Food* f = dynamic_cast<Food*>(obj))
    {
        f -> eaten = true;
        add_segments(segments_per_food);
        f -> apply_effect(this);
        food_boost = true;
        boost_duration.restart();
        decay_timer.restart();
    }
}

void fix_rotation(double& rotation)
{
    if (rotation > 2 * M_PI)
    {
        rotation = 0;
    }
    else if (rotation < 0)
    {
        rotation = 2 * M_PI;
    }
}

void Worm::reset_body()
{
    *upper_body_connector = Vector2f(x, y-width);
    *lower_body_connector = Vector2f(x, y+width);
    std::shared_ptr<Worm_segment> tmp = std::make_shared<Worm_segment>(
                                        Worm_segment(upper_body_connector, 
                                        lower_body_connector)); 
    body.swap(tmp);
    add_segments(base_segment_count);
}

void Worm::decay_segments()
{
    if (decay_timer.getElapsedTime().asMilliseconds() > decay_tick && 
        body -> get_segment_count() > base_segment_count)
    {
        body -> remove_last_segment();
        decay_timer.restart();
    }
}

void Worm::update_body()
{
    body -> update(rotation);
    *upper_body_connector = Vector2f(x + width * sin(rotation), 
                                     y - width * cos(rotation));
    *lower_body_connector = Vector2f(x - width * sin(rotation), 
                                     y + width * cos(rotation));
}

void Worm::update(Time const& delta)
{
    if (boost_duration.getElapsedTime().asSeconds() > settings.at("Special food boost duration") && food_boost)
    {
        velocity = settings.at("Worm velocity");
        rotation_per_tick = 0.1;
        width = settings.at("Worm width") / 2;
        food_boost = false;
    }

    fix_rotation(rotation);
    decay_segments();
    update_body();

    for (auto key : keys)
    {
        if ((key.first == Keyboard::D || key.first == Keyboard::Right) && 
             key.second)
        {
            rotation += rotation_per_tick;
        }
        else if ((key.first == Keyboard::A || key.first == Keyboard::Left) && 
                  key.second)
        {
            rotation -= rotation_per_tick;
        }

        linear_move(delta);
    }
}

void Worm::draw(RenderWindow& window)
{
    body -> draw(window);

    CircleShape circle;
    circle.setRadius(width);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(x, y);
    circle.setOrigin(width, width);
    window.draw(circle);
}

std::shared_ptr<Worm_segment> Worm::get_body()
{
    return body;
}

void Worm::score_goal()
{
    ++score;
    has_scored = true;
}

int Worm::get_score()
{
    return score;
}

void Worm::reset_position()
{
    if (name == "Player 1")
    {
        x = 100;
        y = 350;
        rotation = 0;
    }
    else if (name == "Player 2")
    {
        x = settings.at("Window width") - 100;
        y = 350;
        rotation = M_PI;
    }

    reset_body();
}

std::string Worm::get_name()
{
    return name;
}

void Worm::set_velocity(double const v)
{
    velocity = v;
}

double Worm::get_rotation_per_tick() const
{
    return rotation_per_tick;
}

void Worm::set_rotation_per_tick(double const rpt)
{
    rotation_per_tick = rpt;
}

void Worm::set_width(int const w)
{
    width = w;
}