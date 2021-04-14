#include "Movable_object.h"
#include <cmath>
#include <iostream>

using namespace sf;

Movable_object::Movable_object(double x, double y, int widht, int height)
: Game_object{x, y, widht, height} {}

double Movable_object::get_rotation() const
{
    return rotation;
}

double Movable_object::get_velocity() const
{
    return velocity;
}

void Movable_object::linear_move(Time delta)
{
    x += delta.asMilliseconds() * cos(rotation) * velocity / 100;
    y += delta.asMilliseconds() * sin(rotation) * velocity / 100;
}

void Movable_object::process_keypress(Keyboard::Key const& key)
{}

bool Movable_object::is_colliding(Game_object* obj)
{
    return x < obj -> get_x() + obj -> get_width() &&
            x + width > obj -> get_x() &&
            y < obj -> get_y() + obj -> get_height() &&
            y + height > obj -> get_y();
}