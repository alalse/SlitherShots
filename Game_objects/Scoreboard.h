/**
 * \class Scoreboard
 * the class for the score display
 * visible in the upper corners. 
 */


#pragma once

#include <SFML/Graphics.hpp>
#include "Worm.h"
#include "Static_object.h"

class Scoreboard : public Static_object
{
    public:
    ///Create a scoreboard object
    Scoreboard(double const x, double const y, Worm* worm);
    ///draw the scoreboard in the window
    void draw(sf::RenderWindow& window) override;

    private:
    ///the font that the numbers use
    sf::Font font;
    ///Pointer to the worm that the scoreboard belongs to
    Worm* worm;
};