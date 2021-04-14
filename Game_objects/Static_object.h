/**
 * \class Static_object
 * Parent class for the static game objects.
 * I.e the walls, goals, scoreboards and the middle line.
 */

#pragma once

#include "Game_object.h"

class Static_object : public Game_object
{
    public:
    ///Create a Static_object object
    Static_object(double x, double y, int w, int h);
};