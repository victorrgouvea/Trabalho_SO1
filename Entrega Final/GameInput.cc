#include "GameInput.h"

__BEGIN_API

GameInput::GameInput()
{
    if ((this->_eventQueue = al_create_event_queue()) == NULL)
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
    al_register_event_source(_eventQueue, al_get_keyboard_event_source());
}

void GameInput::run()
{
    while (!GameConfigs::finished)
    {
        al_get_keyboard_state(&inputState);
        Thread::yield();
    }
}

act::action GameInput::getInputEvent() {
  if (al_key_down(&inputState, ALLEGRO_KEY_W)) {
     return act::action::MOVE_UP;
  }
  if (al_key_down(&inputState, ALLEGRO_KEY_D)) {
     return act::action::MOVE_RIGHT;
  }
  if (al_key_down(&inputState, ALLEGRO_KEY_S)) {
     return act::action::MOVE_DOWN;
  }
  if (al_key_down(&inputState, ALLEGRO_KEY_A)) {
     return act::action::MOVE_LEFT;
  }
  if (al_key_down(&inputState, ALLEGRO_KEY_SPACE)) {
     return act::action::FIRE_PRIMARY;
  }
  if (al_key_down(&inputState, ALLEGRO_KEY_1)) {
     return act::action::FIRE_SECONDARY;
  }

}

__END_API