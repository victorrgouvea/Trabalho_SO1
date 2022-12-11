
#ifndef GAMEINPUT_H
#define GAMEINPUT_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "thread.h"
#include "traits.h"
#include "MainThread.h"
#include "Sprite.h"
#include "Vector.h"
#include "Action.h"

__BEGIN_API

class GameInput
{

public:
    GameInput();

    void init();
    void run();
    act::action getInputEvent();

private:
    ALLEGRO_KEYBOARD_STATE inputState;
    ALLEGRO_EVENT_QUEUE *_eventQueue;
    float startTime = 0;
    float currentTime = 0;
    
};

__END_API

#endif