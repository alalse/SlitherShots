#include "Framework/Game_engine.h"
#include "Framework/Settings_handler.h"
#include <iostream>

using namespace sf;

int main() 
{
  int window_height = Settings_handler::get_setting("Window height");
  int window_width = Settings_handler::get_setting("Window width");

  ContextSettings settings;
  settings.antialiasingLevel = 4; //gör detta något alls?

  Game_engine game{"SlitherShots!", settings, window_width, window_height};
  game.window.setKeyRepeatEnabled(false);
  game.window.setVerticalSyncEnabled(true);
  game.window.setFramerateLimit(60);

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

//Fullscreen och upplösningsalternativ. (Se till att allt skalas upp/ner korrekt)
//Styla till menu_state (kolla på animering, "blockig font" och rörliga objekt?)
//Applicera samma stil på gamemodes och help state (i gamemodes: en setting per rad centrerad på skärmen med pilar på vardera sida som pekar på nästa mindre/större värde på inställningen?)
//Byt ut alla pekare mot smartpekare! (åtminstone undersök hur de fungerar/om de kan göra samma saker som nuvarande pekare)
//Rigid body collisions (Box2D? https://box2d.org/documentation/)