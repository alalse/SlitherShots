/**
 * \class Gamemodes_state
 * \brief Gamemodes_state object
 *
 * A class providing an in-application way of editing and customizing 
 * the settings in the external file "settings.txt".
 */

#pragma once

#include "../Framework/Game_state.h"

class Gamemodes_state : public Game_state
{
    public:
    ///Creates a Gamemodes_state.
    Gamemodes_state();

    ///Process an event.
    void process_event(Game_engine* game, sf::Event const& event) override;

    ///Updates state logic, CURRENTLY UNUSED.
    void update(Game_engine* game, sf::Time const& delta) override;

    ///Draw objects of the state.
    void draw(sf::RenderWindow& window) override;

    private:
    ///Int keeping track of selected option.
    unsigned int selected_option;

    ///Font of all text in Gamemodes_state.
    sf::Font font;

    ///Background image of Gamemodes_state.
    sf::Texture background_image;

    ///Gets the name of a setting in 'settings' at index 'index'.
    std::string get_setting_at_index(int index);
};