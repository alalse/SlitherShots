/**
 * \class Goal
 * this is the class for the goal
 * object. It's a child of Static_object 
 * and functions alot like a wall. However 
 * it contains extra member variables, for example 
 * a pointer to the opposing Worm which is used 
 * to increase said worm's score when a ball collides 
 * the goal.
 */

#pragma once

#include "Static_object.h"
#include "Worm.h"

class Goal : public Static_object
{
    public:
    ///Create Goal object
    Goal(double const x, double const y, int const width, int const height);
    ///Set the oppponent variable
    void set_opponent(Worm* o);
    ///return pointer to the opposing Worm
    Worm* get_opponent();

    private:
    ///an instance of an sfml-rectangle, used when drawing the goal
    sf::RectangleShape rect;
    ///Draw the goal in the window
    void draw(sf::RenderWindow& window) override;
    /**
     * \brief Pointer to the opposing worm
     * Pointer to the worm that is on the opposite 
     * side of the playing field. Used when the ball collides 
     * whit the goal to increase the opposing players score.
     */
    Worm* opponent;
};