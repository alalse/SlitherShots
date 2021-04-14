#include "Game_object.h"

Game_object::Game_object(double x, double y, int w, int h)
: x{x}, y{y}, width{w}, height{h} {}

double Game_object::get_x() const
{
    return x;
}

double Game_object::get_y() const
{
    return y;
}

int Game_object::get_width() const
{
    return width;
}

int Game_object::get_height() const
{
    return height;
}

