#include "Speed_food.h"

using namespace sf;

Speed_food::Speed_food(double const x, double const y, double const p)
: Food{x, y}, power{p}
{
    circle.setFillColor(Color::Blue);
}

void Speed_food::apply_effect(Worm* w)
{
    w -> set_velocity(w -> get_velocity() + power);
    w -> set_rotation_per_tick(w -> get_rotation_per_tick() + (power / 50));
}