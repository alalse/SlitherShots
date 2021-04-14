/**
 * \class Line
 * This class represents the middle 
 * line that seperates the worms to their 
 * sides of the field.
 */

#pragma once

#include "Static_object.h"

class Line : public Static_object
{
    public:
    ///Create an instance of the class
    Line(double x, double y, int width, int height);

    private:
    ///an instance of an sfml-rectangle, used when drawing the Line
    sf::RectangleShape rect;
    ///Draw the line in the window
    void draw(sf::RenderWindow& window) override;
};