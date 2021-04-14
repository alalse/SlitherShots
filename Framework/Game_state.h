/**
 * \class Game_state
 * This is the parent class for the different 
 * Game states that the game consists of. 
 * a game state is for example the start menu 
 * or the game itself. The states are stored in 
 * a stack inside of a Game_engine object.
 */

#pragma once

#include "Game_engine.h"

class Game_engine;

class Game_state
{
    public:
    virtual ~Game_state() {};

    ///Process an event
    virtual void process_event(Game_engine* game, sf::Event const& event) = 0;

    ///Updates state logic
    virtual void update(Game_engine* game, sf::Time const& delta) = 0;

    ///Draw objects of state
    virtual void draw(sf::RenderWindow& window) = 0;
};