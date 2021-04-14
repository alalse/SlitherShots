/**
 * \class Wall
 * the class of the bounding walls on the top 
 * and bottom of the playing field
 */
#pragma once

#include "Static_object.h"

class Wall : public Static_object
{
    public:
    ///Create a wall object.
    Wall(double x, double y, int width, int height);

    private:
    ///A rectangle shape used for drawing the wall.
    sf::RectangleShape rect;
    ///draws the wall in the window
    void draw(sf::RenderWindow& window) override;
};