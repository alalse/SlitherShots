#include "Wall.h"

using namespace sf;

Wall::Wall(double x, double y, int width, int height)
: Static_object{x,y,width,height}
{
    rect.setPosition(x, y);
    rect.setSize(Vector2f(width, height));
    rect.setFillColor(Color(107, 107, 107));
}

void Wall::draw(sf::RenderWindow& window)
{
    window.draw(rect);
}