/**
 * \class Worm_segment
 * \brief Worm_segment object
 *
 * A class used to represent a Worm's body. Only
 * useful when chain togehter with other worm_segment objects
 * or a Worm object.
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Worm_segment
{
    public:
    /** \brief Creates a Worm_segment object
      * \param std::shared_ptr\<sf::Vector2f> const p1 and std::shared_ptr\<sf::Vector2f> const p2 are pointers to this segment's connection points.
      * 
      * Creates a Worm_segment object
      * */
    Worm_segment(std::shared_ptr<sf::Vector2f> const p1, 
                 std::shared_ptr<sf::Vector2f> const p2);

    ///Adds 'X' amount of extra segments after the last segment.
    void add_segments(int amount);

    ///Removes the last segment
    void remove_last_segment();

    ///Returns total number of segments in segment chain
    int get_segment_count();

    //Updates the shared_ptrs and rotation of this segment and the next
    void update(double const r);

    /** \brief Draws the worm_segment.
      * \param sf::RenderWindow& window to draw onto.
      * 
      * Draws a ConvexShape over the position of the four shared_ptrs.
      * */
    void draw(sf::RenderWindow& window);

    ///Returns the local_bounds of the segment
    sf::FloatRect get_bounds();

    ///Returns the rotation of the segment
    double get_rotation();
    
    ///Shared_ptr to next segment in chain
    std::shared_ptr<Worm_segment> next;

    ///Shared_ptr to previous p3
    std::shared_ptr<sf::Vector2f> const p1;

    ///Shared_ptr to previous p4
    std::shared_ptr<sf::Vector2f> const p2;

    ///Shared_ptr to next p1
    std::shared_ptr<sf::Vector2f> p3;

    ///Shared_ptr to next p2
    std::shared_ptr<sf::Vector2f> p4;

    ///Graphical representation of segment
    sf::ConvexShape segment;

    private:

    ///Rotation of segment
    double rotation;
};