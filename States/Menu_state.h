/**
 * \class Menu_state
 * \brief Menu_state object
 *
 * A class connecting the game's different aspects
 * through a main menu.
 */

#pragma once

#include "../Framework/Game_state.h"
#include <vector>

class Menu_state : public Game_state
{
    public:
    ///Creates a Menu_state object
    Menu_state();

    ~Menu_state();

    ///Process an event.
    void process_event(Game_engine* game, sf::Event const& event) override;

    ///Updates state logic. CURRENTLY UNUSED.
    void update(Game_engine* game, sf::Time const& delta) override;

    ///Draws objects of the state.
    void draw(sf::RenderWindow& window);

    private:
    ///Background image Menu_state.
    sf::Texture background_image;

    ///Font of all text in Menu_state.
    sf::Font font;

    ///Vector containing all menu items.
    std::vector<sf::Text*> menu_items;

    ///Int keeping track of selected menu
    int selected_menu;
};