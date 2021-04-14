/**
 * \class Gamemodes_state
 * \brief Gamemodes_state object
 *
 * A class providing an in-application way of editing and customizing 
 * the settings in the external file "settings.txt".
 */

#pragma once

#include "../Framework/Game_state.h"
#include "../Framework/Settings_handler.h"

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
    ///Instance of Settings_handler enabling communication with the external settings file.
    Settings_handler sh;

    ///Int keeping track of selected option.
    unsigned int selected_option;

    ///Font of all text in Gamemodes_state.
    sf::Font font;

    ///Background image of Gamemodes_state.
    sf::Texture background_image;

    ///Loaded data from settings file.
    std::map<std::string, int> settings;

    ///Gets the key of element in 'settings' att index 'index'.
    std::string get_key(int index);

    ///Returns a different value to increment or decrement setting with depending on setting at key.
    int change_value(std::string key);
};