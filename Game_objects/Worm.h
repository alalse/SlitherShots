/**
 * \class Worm
 * \brief Worm game_object
 *
 * A class used to represent a Worm and a player
 * with functionality for collision with all types of game_objects,
 * scoring goals and handling of the worm's body.
 */

#pragma once

#include "Movable_object.h"
#include "Worm_segment.h"
#include <memory>

class Worm : public Movable_object
{
    public:
    ///shared_ptr connecting the original top of the head with the original top of the worm's body
    std::shared_ptr<sf::Vector2f> upper_body_connector;

    ///shared_ptr connecting the original bottom of the head with the original bottom of the worm's body
    std::shared_ptr<sf::Vector2f> lower_body_connector;

    ///Switch other objects can inspect to see if the worm has scored a goal
    bool has_scored;

    /** \brief Creates a Worm object
      * \param std::string name of worm/player.
      * 
      * Creates a Worm object associated with specified player.
      * Only valid names are "Player 1" and "Player 2" or else the
      * worm will have invalid data.
      * */
    Worm(std::string name);

    /** \brief Process a keypress
      * \param sf::Keyboard::Key const& key.
      * 
      * Processes a keypress and depending on key
      * switches a bool symbolizing that key from
      * true to false or from false to true.
      * */
    void process_keypress(sf::Keyboard::Key const& key);

    /** \brief Process a collision.
      * \param Game_object* obj to object of collision.
      * Calculates new position and rotation after collision 
      * with different game objects. If colliding with food
      * the food gets deleted, the worm grows in size and if
      * the food had a special effect -> apply it to the worm.
      * */
    void collide(Game_object* obj) override;

    /** \brief Updates variables of Worm.
      * \param Delta time since last update.
      * 
      * Keeps the worm's rotation between 0 and 2PI, 
      * updates it's rotation depending on keys pressed and updates 
      * the worm's position with delta time. The function also
      * reverts special food effects depending on how long it's
      * been active and decay's one of the extra segments gained from food
      * if a long enough duration has went by since last decay.
      * */
    void update(sf::Time const& delta) override;

    /** \brief Draws the worm and it's body.
      * \param sf::RenderWindow& window to draw onto.
      * 
      * Draws a circle at the Worm's position. Also draws a custom
      * sf::ConvexShape for every segment in it's body.
      * */
    void draw(sf::RenderWindow& window) override;

    ///Returns a shared_ptr to the first segment in the worm's body.
    std::shared_ptr<Worm_segment> get_body();

    ///Increases the score of the worm and sets has_scored to true.
    void score_goal();

    ///Returns the worm's score.
    int get_score();

    ///Returns the name of the worm.
    std::string get_name();

    ///Resets the position of the worm to initial values.
    void reset_position() override;
    
    ///Sets the velocity of the worm.
    void set_velocity(double const v);

    ///Gets current rotation per tick.
    double get_rotation_per_tick() const;

    ///Sets the rotation per tick of the worm.
    void set_rotation_per_tick(double const rpt);

    ///Sets the width of the worm.
    void set_width(int const w);

    private:

    ///The name of the worm.
    std::string name;

    ///Shared_ptr to the first segment in body.
    std::shared_ptr<Worm_segment> body;

    ///Rotation change per tick.
    double rotation_per_tick;

    ///Extra segments for every piece of food eaten.
    int segments_per_food;

    ///Goals scored.
    int score;

    ///Time in milliseconds between the decay of extra segments.
    int decay_tick;

    ///Initial number of segments.
    int base_segment_count;

    ///Timer used to determine when to decay a worm segment.
    sf::Clock decay_timer;

    ///Map containing keys used to turn and if they are pressed or not.
    std::map<sf::Keyboard::Key, bool> keys;

    ///Map containing settings information loaded from Settings_handler class.
    std::map<std::string, int> settings;

    ///Switch telling if a food boost is active.
    bool food_boost;

    ///Timer used to determine when to remove food boost.
    sf::Clock boost_duration;

    /** \brief Adds 'X' amount of extra segments.
      * \param int const amount.
      * 
      * Recursivly walks through each segment and
      * adds 'X' extra segments to the end of the last segment.
      * */
    void add_segments(int const amount);

    /** \brief Removes the last segment in body.
      * \param int const amount.
      * 
      * Recursivly walks through each segment and
      * removes the last one it finds.
      * */
    void remove_last_segment();

    /** \brief Remove an extra segment after a set interval.
      * 
      * Removes the last segment in the worm's body if the
      * elapsed time in the 'decay_timer' is more than a
      * set amount of seconds and there are more than the
      * initial amount of segments currently in the body.
      * */
    void decay_segments();

    ///Updates the position and rotation of all segments
    void update_body();

    ///Removes the entire body and creates a new one.
    void reset_body();
};