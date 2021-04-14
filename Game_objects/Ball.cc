#include "Ball.h"
#include "Worm.h"
#include "Wall.h"
#include "Goal.h"
#include "../Framework/Settings_handler.h"

#include <iostream>
#include <cmath>

using namespace sf;

Ball::Ball()
: Movable_object{0,0,0,0}
{   
    Settings_handler sh;
    std::map<std::string, int> settings = sh.load();
    window_width = settings.at("Window width");
    window_height = settings.at("Window height");
    width = settings.at("Ball size");
    height = settings.at("Ball size");
    x = window_width / 2 - (width / 2);
    y = window_height / 2 - (height / 2);
    base_velocity = velocity = settings.at("Ball velocity");
    rotation = ((double) rand() / (RAND_MAX)) * M_PI;

    circle.setFillColor(Color::Green);
    circle.setRadius(width/2);
    circle.setPosition(x,y);
}

void Ball::increase_velocity()
{
    velocity += 1;
}

void Ball::update(Time const& delta)
{
    if (rotation > 2 * M_PI)
    {
        rotation -= 2 * M_PI;
    }
    else if (rotation < 0)
    {
        rotation += 2 * M_PI;
    }

    linear_move(delta);
}

void Ball::draw(RenderWindow& window)
{
    circle.setPosition(x,y);
    circle.setRadius(width/2);
    window.draw(circle);
}

void Ball::collide(Game_object* obj)
{
    if (Worm* w = dynamic_cast<Worm*>(obj))
    {
        rotation = w -> get_rotation();
        increase_velocity();
    }
    else if (dynamic_cast<Wall*>(obj))
    {
        if (rotation <= M_PI && rotation > 0)
        {
            y = window_height - height - 20;
        }
        else
        {
            y = 20;
        }
        
        rotation += 2 * (M_PI - rotation);
    }
    else if (dynamic_cast<Goal*>(obj))
    {
        Goal* goal = dynamic_cast<Goal*>(obj);
        goal -> get_opponent() -> score_goal();
    }
}

double dot_product(Vector2f const& a, Vector2f const& b)
{
    return a.x * b.x + a.y * b.y;
}

void Ball::collide(std::shared_ptr<Worm_segment> seg)
{
    FloatRect seg_bounds = seg -> get_bounds();
    
    //If boundingbox collision
    if (x < seg_bounds.left + seg_bounds.width &&
        x + width > seg_bounds.left &&
        y < seg_bounds.top + seg_bounds.height &&
        y + height > seg_bounds.top)
    {
        //Difference between ball and segment center point
        double diff_x = ((seg_bounds.left + (seg_bounds.width / 2.0)) - (x + (width / 2.0)));
        double diff_y = ((seg_bounds.top + (seg_bounds.height / 2.0)) - (y + (height / 2.0)));
        Vector2f diff = Vector2f(diff_x, diff_y);

        //The ball's direction
        Vector2f ball_direction = Vector2f(cos(rotation), sin(rotation));

        //If ball is travelling towards the segment -> do collision.
        if (dot_product(diff, ball_direction) > 0)
        {
            //The segment's direction
            Vector2f segment_direction = Vector2f(cos(seg -> get_rotation()), sin(seg -> get_rotation()));
            
            //Reflect the direction of the ball from the direction of the segment
            double dot = dot_product(ball_direction, segment_direction);
            double length_squared = pow(segment_direction.x, 2) + pow(segment_direction.y, 2);
            Vector2f proj = Vector2f(segment_direction.x * dot / length_squared, segment_direction.y * dot / length_squared);
            Vector2f reflection = Vector2f(-ball_direction.x + (2 * proj.x), -ball_direction.y + (2 * proj.y));

            //Calculate new ball rotation from reflection
            double new_rotation = atan2(reflection.y, reflection.x);
            rotation = new_rotation;
        }
    }
}

void Ball::reset_position()
{
    x = window_width / 2 - (width / 2);
    y = window_height / 2 - (height / 2);

    rotation = ((double) rand() / (RAND_MAX)) * M_PI;
    velocity = base_velocity;
}