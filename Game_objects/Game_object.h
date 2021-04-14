/**
 * \class Game_object
 * this is the parent class for all the visible 
 * objects in the play state. 
 */

#pragma once

#include <SFML/Graphics.hpp>

class Game_object
{
    public:
    ///Create an instance of Game_object
    Game_object(double x, double y, int w, int h);
    ///Delete the instance of Game_object
    virtual ~Game_object() {};
    ///return the object's x-coordinate
    double get_x() const;
    ///return the object's x-coordinate
    double get_y() const;
    ///return the object's width
    int get_width() const;
    ///return the object's height
    int get_height() const;
    ///draws the object in the window
    virtual void draw(sf::RenderWindow& window) = 0;

    protected:
    ///the object's x-coordinate
    double x;
    ///the object's y-coordinate
    double y;
    ///the object's width in pixels
    int width;
    ///the object's height in pixels
    int height;
};