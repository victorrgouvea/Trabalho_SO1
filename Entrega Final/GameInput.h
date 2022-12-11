
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
    bool getInputEvent(act::action key);

    ALLEGRO_EVENT_QUEUE *_inputQueue;
private:
    ALLEGRO_KEYBOARD_STATE inputState;
    float startTime = 0;
    float currentTime = 0;
    
};

__END_API

#endif