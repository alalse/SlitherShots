#include "Framework/Game_engine.h"
#include "Framework/Settings_handler.h"
#include "States/Menu_state.h"
#include <iostream>

using namespace sf;

/**
 * Initializes and runs the game
 */
int main()
{
    Settings_handler sh;
    std::map<std::string, int> game_settings = sh.load();
    int window_width = game_settings.at("Window width");
    int window_height = game_settings.at("Window height");

    ContextSettings settings;
    settings.antialiasingLevel = 8;

    Game_engine game{"SlitherShots!", settings, window_width, window_height};
    game.window.setKeyRepeatEnabled(false);
    game.window.setVerticalSyncEnabled(true);
    game.window.setFramerateLimit(60);
    game.push_state(new Menu_state());

    Clock clock;

    while(game.running)
    {  
        if (game.exit_current_state)
        {
            game.pop_state();
        }
        
        Event event;
        while(game.window.pollEvent(event))
        {
            game.process_event(event);
        }

        Time delta = clock.restart();
        game.update(delta);
        game.draw();
    }

    game.cleanup();
    return 0;
}


/** \brief A useful method.
      * \param level an integer setting how useful to be
      * \return Output that is extra useful
      * 
      * This method does unbelievably useful things.  
      * And returns exceptionally useful results.
      * Use it everyday with good health.
      */