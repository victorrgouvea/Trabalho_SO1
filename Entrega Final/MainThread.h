#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <iostream>
#include "cpu.h"
#include "traits.h"
#include "thread.h"
#include "semaphore.h"

#include "Engine.h"
#include "GameInput.h"
#include "GameWindow.h"
#include "Player.h"

__BEGIN_API

class MainThread
{
public:
    MainThread() {}
    ~MainThread() {}
    static Player *player;
    static GameWindow * gameWindow;
    static GameInput *gamekeyb;
    static Engine *engine;
    static void run(void *name)
    {
        windowT = new Thread(windowInit);
        playerT = new Thread(playerInit);
        inputT = new Thread(inputInit);
        engineT  = new Thread(engineInit);
        playerT->join();
        windowT->join();
        inputT->join();
        engineT->join();
        delete playerT;
        delete windowT;
        delete inputT;
        delete engineT;
    }

private:
    static void windowInit();
    static void playerInit();
    static void inputInit();
    static void engineInit();


    static Thread *playerT;
    static Thread *windowT;
    static Thread *inputT;
    static Thread *engineT;
};

__END_API

#endif
