/**
 * \class Movable_object
 * this is the parent class for all the 
 * game objects that move, i.e the ball and the worms.
 */

#pragma once

#include "Game_object.h"

class Movable_object : public Game_object
{
    public:
    ///Create a Movable_object object.
    Movable_object(double x, double y, int widht, int height);
    ///Delete the object.
    virtual ~Movable_object() {};
    ///check if the object's position relative to the pointed to object would result in a collision.
    virtual bool is_colliding(Game_object* obj);
    /**
     * \brief collides with the object pointed to
     * \param a pointer to the game object that the object is colliding with
     * this function is called when a movable object
     * collides with any game object, the code that 
     * is ran depends on what subclass the movable 
     * object is, the sub classes override the function
     * with their own code because different types of movable objects
     * behave differently when colliding.
     */
    virtual void collide(Game_object* obj) = 0;
    ///Updates the position and rotation of the object for every frame.
    virtual void update(sf::Time const& delta) = 0;
    ///returns the rotation variable.
    double get_rotation() const;
    ///returns the velocity variable.
    double get_velocity() const;
    ///resets the object to it's starting position
    virtual void reset_position() = 0;
    ///processes keyboard input to control the object
    virtual void process_keypress(sf::Keyboard::Key const& key);

    protected:
    ///updates the coordinate values of the object so that it moves linearly in the specified direction (rotation)
    void linear_move(sf::Time delta);
    ///the velocity he object visibly travels in
    double velocity;
    ///The direction that the object is travelling in as a degree in radian.
    double rotation;
};