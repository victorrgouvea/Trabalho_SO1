#include "GameInput.h"

__BEGIN_API

GameInput::GameInput()
{
    if ((_inputQueue = al_create_event_queue()) == NULL)
    {
        std::cout << "error, could not create event queue\n";
        exit(1);
    }

    // install keyboard
    if (!al_install_keyboard())
    {
        std::cerr << "Could not install keyboard\n";
    }

    // register keyboard
    al_register_event_source(_inputQueue, al_get_keyboard_event_source());
}

void GameInput::run()
{
     
    while (MainThread::gameWindow->getGameRunning())
    {
        al_get_keyboard_state(&inputState);
        Thread::yield();
    }
}

bool GameInput::getInputEvent(act::action key)
{
   if (key == act::action::MOVE_UP)
      return al_key_down(&inputState, ALLEGRO_KEY_W);
   else if (key == act::action::MOVE_DOWN)
      return al_key_down(&inputState, ALLEGRO_KEY_S);
   else if (key == act::action::MOVE_LEFT)
      return al_key_down(&inputState, ALLEGRO_KEY_A);
   else if (key == act::action::MOVE_RIGHT)
      return al_key_down(&inputState, ALLEGRO_KEY_D);
   else if (key == act::action::FIRE_PRIMARY)
      return al_key_down(&inputState, ALLEGRO_KEY_SPACE);
   else if (key == act::action::FIRE_SECONDARY)
      return al_key_down(&inputState, ALLEGRO_KEY_1);
    else
      return false;
       
}

__END_API