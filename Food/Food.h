/**
 * \class Food
 * \brief Food game_object
 *
 * A class used to represent food.
 */

#pragma once

#include "Static_object.h"
#include "../Game_objects/Worm.h"

class Food : public Static_object
{
    public:
    bool eaten;

    /** \brief Creates a Food object.
      * \param x, y Food coordinates.
      * 
      * Creates a food object.
      * */
    Food(double const x, double const y);

    virtual ~Food() {};

    /** \brief Applies the effect of the food on a worm.
      * \param Worm* pointer to the worm to apply the effect onto.
      * */
    virtual void apply_effect(Worm* w);

    /** \brief Draws a colored circle at the food's position.
      * \param sf::Renderwindow to draw onto.
      * */
    void draw(sf::RenderWindow& window) override;

    protected:
    ///Graphical representation of food
    sf::CircleShape circle;
};