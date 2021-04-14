#include "Game_engine.h"
#include "Game_state.h"
#include "../States/Play_state.h"
#include <string>

using namespace sf;

Game_engine::Game_engine(std::string const title, ContextSettings settings, 
                         int const width, int const height)
: window{VideoMode(width, height), title, Style::Default, settings} {}

void Game_engine::cleanup()
{
    while(states.size() > 0)
    {
        pop_state();
    }

    window.close();
}

void Game_engine::push_state(Game_state* state)
{
    states.push(state);
}

void Game_engine::pop_state()
{
    Game_state* state = states.top();
    states.pop();
    delete state;
    exit_current_state = false;
}

void Game_engine::process_event(Event const& event)
{
    states.top() -> process_event(this, event);
}

void Game_engine::update(Time const& delta)
{
    states.top() -> update(this, delta);
}

void Game_engine::draw()
{
    states.top() -> draw(window);
}