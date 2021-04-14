/**
 * \class Help_state
 * \brief Help_state object
 *
 * A class providing players with information on how
 * to play the game.
 */

#pragma once

#include "../Framework/Game_state.h"
#include <vector>

class Help_state : public Game_state
{
    public:
    ///Creates a Help_state object.
    Help_state();

    ///Process an event.
    void process_event(Game_engine* game, sf::Event const& event) override;

    ///Updates state logic.
    void update(Game_engine* game, sf::Time const& delta) override;

    ///Draws current slide.
    void draw(sf::RenderWindow& window) override;

    private:

    ///Int keeping track of current slide.
    int current_slide;

    ///Vector containing all slides.
    std::vector<sf::Texture> slides;
};