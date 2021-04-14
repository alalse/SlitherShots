/**
 * \class Ball
 * \brief Ball game_object
 *
 * A class used to represent a moving ball
 * with functionality for collision and reset to
 * start position.
 */

#pragma once

#include "Movable_object.h"
#include "Worm_segment.h"

class Ball : public Movable_object
{
    public:

    ///Creates a ball
    Ball();

    ~Ball() = default;

    /** \brief Updates variables of ball.
      * \param Delta time since last update.
      * 
      * Keeps the ball's rotation between 0 and 2PI
      * and updates the ball's position with delta time.
      * */
    void update(sf::Time const& delta) override;

    ///Draws a circle at the ball's position.
    void draw(sf::RenderWindow& window) override;

    /** \brief Process a collision.
      * \param Game_object* to object of collision.
      * 
      * Calculates new rotation after collision with
      * different game_objects. Collision with a 
      * Worm object increases ball velocity and rotates the 
      * ball in the same direction as the Worm. Collision
      * with a Wall object reflects the ball and collision with
      * a Goal object gives a Worm a point.
      * */
    void collide(Game_object* obj) override;

    /** \brief Collision with Worm_segment object.
      * \param std::shared_ptr<Worm_segment> to segment of collision.
      * 
      * Calculates new rotation after collision with
      * a Worm_segment object using vector reflection.
      * */
    void collide(std::shared_ptr<Worm_segment> seg);

    ///Resets ball position to center of screen and gives it a new random rotation
    void reset_position() override;

    private:

    ///Ball base velocity
    int base_velocity;

    ///Window width for use in reset_position()
    int window_width;

    ///Window height for use in reset_position()
    int window_height;

    ///Graphical representation of ball
    sf::CircleShape circle;

    ///Increases ball velocity with one unit
    void increase_velocity();
};