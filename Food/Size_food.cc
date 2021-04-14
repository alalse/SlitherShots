#include "Size_food.h"

using namespace sf;

Size_food::Size_food(double const x, double const y, double const p)
: Food{x, y}, power{p}
{
    circle.setFillColor(Color::Yellow);
}

void Size_food::apply_effect(Worm* w)
{
    w -> set_width(w -> get_width() + power);
}