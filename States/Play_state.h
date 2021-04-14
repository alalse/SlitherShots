/**
 * \class Play_state
 * \brief Play_state object
 *
 * A class handling the actual game
 */

#pragma once

#include "../Framework/Game_state.h"
#include "../Game_objects/Ball.h"
#include "../Game_objects/Goal.h"
#include "../Game_objects/Wall.h"
#include "../Game_objects/Worm.h"
#include "../Game_objects/Line.h"
#include "../Game_objects/Scoreboard.h"
#include <vector>
#include <string>

class Play_state : public Game_state
{
    public:
    ///Creates a Play_state object.
    Play_state();

    ~Play_state();

    ///Process an event.
    void process_event(Game_engine* game, sf::Event const& event) override;

    ///Process a collision between a Movable_object and Static_object.
    void static_object_collision(Movable_object* mov);

    ///Process a collision between two Movable_objects.
    void movable_object_collision(Movable_object* mov);

    ///Process a collision between a Ball and Segment object.
    void ball_to_segment_collision(Ball* ball);

    ///Updates state logic.
    void update(Game_engine* game, sf::Time const& delta) override;

    /** \brief Updates food
      * 
      * Removes all food marked with eaten = true.
      * Counts current amount of food and if current amount of
      * food is less than the maximum amount and the time since last
      * food spawn is less than a set time -> spawn a new piece of food.
      * */
    void update_food(Game_engine* game);

    ///Updates scores and if a worm has reached the amount of goals required to win -> set winner.
    void update_score();

    ///Draws all objects in vectors static_objects and movable_objects.
    void draw(sf::RenderWindow& window) override;

    private:

    ///Switch for checking if someone has won.
    bool someone_has_won;

    ///Name of winner worm
    std::string winner;

    ///Vector containing all static_objects
    std::vector<Static_object*> static_objects;

    ///Vector containing all movable_objects
    std::vector<Movable_object*> movable_objects;

    ///Timer for calculating when to place new food.
    sf::Clock food_timer;

    ///Timer for calculating when to start new round after a goal.
    sf::Clock countdown;

    ///Map of settings loaded from a Settings_handler object.
    std::map<std::string, int> settings;

    ///Resets state and starts another round.
    void reset();
};