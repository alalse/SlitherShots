#include "Food.h"
#include "../Framework/Settings_handler.h"

using namespace sf;

Food::Food(double const x, double const y)
: Static_object{x, y, 10, 10}, eaten{false}
{
    Settings_handler sh;
    std::map<std::string, int> settings = sh.load();
    width = settings.at("Food size");
    height = settings.at("Food size");

    circle.setRadius(width / 2);
    circle.setOrigin(width / 2, height / 2);
    circle.setPosition(x, y);
    circle.setFillColor(Color::Magenta);
}

void Food::apply_effect(Worm* w)
{}

void Food::draw(RenderWindow& window)
{
    window.draw(circle);
}