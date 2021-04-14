/**
 * \class Speed_food
 * \brief Speed_Food game_object
 *
 * A class used to represent food
 * that gives a worm extra speed when eaten.
 */

#pragma once

#include "Food.h"

class Speed_food : public Food
{
    public:

    /** \brief Creates a Speed_food object.
      * \param x, y coordinates.
      * \param power The strength to multiply a worms speed with.
      * 
      * Creates a Speed_food object.
      * */
    Speed_food(double const x, double const y, double const power);

    ~Speed_food() = default;

    /** \brief Applies the effect of the food on a worm.
      * \param Worm* pointer to the worm to apply the effect onto.
      * */
    void apply_effect(Worm* w) override;

    private:

    ///The strength of the food
    double power;
};