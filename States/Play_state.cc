#include "Play_state.h"
#include "Win_state.h"
#include "Worm_segment.h"
#include "../Food/Food.h"
#include "../Food/Speed_food.h"
#include "../Food/Size_food.h"
#include "../Framework/Settings_handler.h"
#include <iostream>
#include <string>
#include <random>

using namespace sf;

Play_state::Play_state()
: someone_has_won{false}
{   
    Settings_handler sh;
    settings = sh.load();

    int window_width = settings.at("Window width");
    int window_height = settings.at("Window height");

    movable_objects.push_back(new Ball());
    movable_objects.push_back(new Worm("Player 1"));
    movable_objects.push_back(new Worm("Player 2"));
    static_objects.push_back(new Goal(0, 0, 20, window_height));
    static_objects.push_back(new Goal(window_width - 20, 0, 20, window_height));
    static_objects.push_back(new Line((window_width / 2) - 25, 0, 50, window_height));
    static_objects.push_back(new Wall(0, 0, window_width, 20));
    static_objects.push_back(new Wall(0, window_height - 20, window_width, window_height));

    Goal* goal1 = dynamic_cast<Goal*>(static_objects[0]);
    Goal* goal2 = dynamic_cast<Goal*>(static_objects[1]);

    Worm* worm1 = dynamic_cast<Worm*>(movable_objects[1]);
    Worm* worm2 = dynamic_cast<Worm*>(movable_objects[2]);

    goal1 -> set_opponent(worm2);
    goal2 -> set_opponent(worm1);

    static_objects.push_back(new Scoreboard(100, 100, worm1));
    static_objects.push_back(new Scoreboard(window_width - 100, 100, worm2));

    food_timer = Clock();
    countdown = Clock();
}

Play_state::~Play_state()
{
    for (Movable_object* mov : movable_objects)
    {
        delete mov;
    }

    for (Static_object* st : static_objects)
    {
        delete st;
    }
}

void Play_state::process_event(Game_engine* game, sf::Event const& event)
{
    switch (event.type)
    {
    case Event::Closed:
        break;

    case Event::KeyPressed:
    case Event::KeyReleased:
        if (event.key.code == Keyboard::Escape)
        {
            game -> exit_current_state = true;
        }

        for (Movable_object* mov : movable_objects)
        {
            mov -> process_keypress(event.key.code);
        }

        break;
    default:
        break;
    }
}

void Play_state::static_object_collision(Movable_object* mov)
{
    for (Static_object* sobj : static_objects)
    {
        if (mov -> is_colliding(sobj))
        {
            mov -> collide(sobj);
        } 
   }
}

void Play_state::movable_object_collision(Movable_object* mov)
{
    for (Movable_object* mov2 : movable_objects)
    {
        if (mov != mov2 && mov -> is_colliding(mov2))
        {
            mov -> collide(mov2);
        } 
    }
}

void Play_state::ball_to_segment_collision(Ball* ball)
{
    std::vector<Worm*> worms;
    for (Movable_object* mov : movable_objects)
    {
        if (Worm* worm = dynamic_cast<Worm*>(mov))
        {
            worms.push_back(worm);
        }
    }
    for (Worm* worm : worms)
    {
        std::shared_ptr<Worm_segment> body = worm -> get_body();
        while (body != nullptr)
        {
            ball -> collide(body);
            body = body -> next;
        }
    }   
}

void Play_state::update_score()
{
    if (dynamic_cast<Worm*>(movable_objects[1]) -> has_scored || 
            dynamic_cast<Worm*>(movable_objects[2]) -> has_scored)
    {
        reset();
    }
    if (dynamic_cast<Worm*>(movable_objects[1]) -> get_score()
        == settings.at("Goals to win"))
    {
        someone_has_won = true;
        winner = dynamic_cast<Worm*>(movable_objects[1]) -> get_name();
    }
        
    if (dynamic_cast<Worm*>(movable_objects[2]) -> get_score()
        == settings.at("Goals to win"))
    {
        someone_has_won = true;
        winner = dynamic_cast<Worm*>(movable_objects[2]) -> get_name();
    }
}

void Play_state::update(Game_engine* game, Time const& delta)
{   
    if (countdown.getElapsedTime().asSeconds() > 3)
    {
        update_food(game);

        for (Movable_object* mov : movable_objects)
        {
            static_object_collision(mov);
            movable_object_collision(mov);

            if (Ball* ball = dynamic_cast<Ball*>(mov))
            {
                ball_to_segment_collision(ball);
            }
        }

        for (Movable_object* mov : movable_objects)
        {
            mov -> update(delta);
        }

        update_score();
        
        if (someone_has_won)
        {
            game -> push_state(new Win_state(winner));
        }
    }    
}

void Play_state::update_food(Game_engine* game)
{
    //Remove eaten food
    for (auto s = static_objects.begin(); s != static_objects.end(); ++s)
    {
        if (Food* f = dynamic_cast<Food*>(*s))
        {
            if (f -> eaten)
            {
                static_objects.erase(s);
                food_timer.restart();
                break;
            }
        }
    }

    //Get current amount of food in static_objects
    int food_amount = std::count_if(static_objects.begin(), static_objects.end(), 
    [](Static_object* s) 
    {
        return dynamic_cast<Food*>(s) != nullptr;
    });

    //Add more food in intervals of 'food_spawnrate' seconds if less than 'max_food' food exists
    if (food_timer.getElapsedTime().asSeconds() > settings.at("Food spawnrate") && 
        food_amount < settings.at("Maximum amount of food at once"))
    {
        std::random_device rd{};
        std::uniform_int_distribution<int> random_x{50, settings.at("Window width") - 50};
        std::uniform_int_distribution<int> random_y{50, settings.at("Window height") - 50};
        unsigned int new_x = random_x(rd);
        unsigned int new_y = random_y(rd);

        //Decides the type of the new food
        std::uniform_int_distribution<int> food_type_dice{0, 2};
        if (food_type_dice(rd) == 0)
        {
            static_objects.push_back(new Speed_food(new_x, new_y, 1.75));
        }
        else if (food_type_dice(rd) == 1)
        {
            static_objects.push_back(new Size_food(new_x, new_y, 5));
        }
        else
        {
            static_objects.push_back(new Food(new_x, new_y));
        }
        
        food_timer.restart();
    }
}

void Play_state::draw(RenderWindow& window)
{
    window.clear();

    for (Movable_object* obj : movable_objects)
    {
        obj -> draw(window);
    }
    
    for (Static_object* obj : static_objects)
    {
        obj -> draw(window);
    }

    if (countdown.getElapsedTime().asSeconds() <= 3)
    {
        Font font;
        font.loadFromFile("Roboto-Regular.ttf");
        std::string content = std::to_string((int)ceil(3 - countdown.getElapsedTime().asSeconds()));
        Text cd_timer{content,font,50};
        FloatRect rect = cd_timer.getLocalBounds();
        cd_timer.setOrigin(rect.left + rect.width / 2, rect.top  + rect.height / 2);
        cd_timer.setPosition(settings.at("Window width") / 2, 200);
        window.draw(cd_timer);
    }

    window.display();
}

void Play_state::reset()
{
    for (Movable_object* obj : movable_objects)
    {
        obj -> reset_position();
    }

    dynamic_cast<Worm*>(movable_objects[1]) -> has_scored = false;
    dynamic_cast<Worm*>(movable_objects[2]) -> has_scored = false;

    countdown.restart();
}