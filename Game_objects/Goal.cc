#include "Goal.h"

using namespace sf;

Goal::Goal(double x, double y, int width, int height)
: Static_object{x, y, width, height}
{
    rect.setPosition(x, y);
    rect.setSize(Vector2f(width, height));
    rect.setFillColor(Color(205, 205, 205));
}

void Goal::draw(RenderWindow& window)
{
    window.draw(rect);
}
void Goal::set_opponent(Worm* o)
{
    opponent = o;
}
Worm* Goal::get_opponent()
{
    return opponent;
}