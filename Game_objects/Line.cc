#include "Line.h"

using namespace sf;

Line::Line(double x, double y, int width, int height)
: Static_object{x, y, width, height} 
{
    rect.setPosition(x, y);
    rect.setSize(Vector2f(width, height));
    rect.setFillColor(Color(255,255,255,128));
}

void Line::draw(RenderWindow& window)
{
    window.draw(rect);
}