#include "Scoreboard.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Scoreboard::Scoreboard(double const x, double const y, Worm* worm)
: Static_object{x, y, 0, 0}, worm{worm}
{
    font.loadFromFile("Roboto-Regular.ttf");
}

void Scoreboard::draw(sf::RenderWindow& window)
{
    Text text{std::to_string(worm -> get_score()), font, 50};
    FloatRect rect = text.getLocalBounds();
    text.setOrigin(rect.left + rect.width / 2, rect.top  + rect.height / 2);
    text.setPosition(x, y);
    text.setOutlineColor(Color(107, 107, 107));
    text.setOutlineThickness(1);
    window.draw(text);
}