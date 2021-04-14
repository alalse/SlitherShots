/**
 * \class Size_food
 * \brief Size_Food game_object
 *
 * A class used to represent food
 * that gives a worm extra width when eaten.
 */

#pragma once

#include "Food.h"

class Size_food : public Food
{
    public:

    /** \brief Creates a Size_food object.
      * \param x, y coordinates.
      * \param power The width to add to a worm.
      * 
      * Creates a Size_food object.
      * */
    Size_food(double const x, double const y, double const power);

    ~Size_food() = default;

    /** \brief Applies the effect of the food on a worm.
      * \param Worm* pointer to the worm to apply the effect onto.
      * */
    void apply_effect(Worm* w) override;

    private:

    ///The strength of the food
    double power;
};