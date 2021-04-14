/**
 * \class Game_engine
 * This is the central class that contains
 * the render window, the gamestates, and the 
 * base functions that main.cc call. 
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <stack>
#include <string>
#include "Game_state.h"

class Game_state;

class Game_engine
{
    public:
    ///Application window
    sf::RenderWindow window;

    ///Application running
    bool running{true};

    ///Switch for removal of top state
    bool exit_current_state{false};

    ///Create a Game_engine class
    Game_engine(std::string const title, sf::ContextSettings settings, 
                int const width = 1600, int const height = 768);

    ///Deallcolate all used memory
    void cleanup();

    ///Push a state to stack of active states
    void push_state(Game_state* state);

    ///Remove top state from the stack of active states
    void pop_state();
    
    ///Sends an event to the top state
    void process_event(sf::Event const& event);

    ///Updates objects in the top state
    void update(sf::Time const& delta);

    ///Draws drawable objects in state
    void draw();

    private:
    /**
     * \brief Stack of all active states
     * A stack that contains all the loaded 
     * game states. When a game state is initialized 
     * it gets put in the stack and the game engine 
     * only updates, displays and processes events on the state
     * at the top. If a state is popped the game updates, etc. 
     * the state below. This can be likened to opening and closing
     * windows that overlap in a GUI.
     */
    std::stack<Game_state*> states;
};