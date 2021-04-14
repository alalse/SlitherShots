/**
 * \class Win_state
 * the class for the game state that is displayed when 
 * a player has won a game.
 */

#pragma once

#include "../Framework/Game_state.h"

class Win_state : public Game_state
{
    public:
    ///Create a Win_state object
    Win_state(std::string w);

    ///Processes user input
    void process_event(Game_engine* game, sf::Event const& event) override;
    ///update functino inhherited from parent class, it does nothing here but has to be overrided because the base method is abstract
    void update(Game_engine* game, sf::Time const& delta);
    ///draws the background image and text in the window
    void draw(sf::RenderWindow& window) override;

    private:
    ///the string that is in the displayed text that corresponds to the winning worm's name
    std::string winner;
    ///the font used in the text
    sf::Font font;
    ///the background image of the state
    sf::Texture background_image;
};