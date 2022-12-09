#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <iostream>
#include "Threads/cpu.h"
#include "Threads/traits.h"
#include "Threads/thread.h"
#include "Threads/semaphore.h"

#include "Window.h"
#include "KeyBoard.h"
#include "PlayerShip.h"
#include "Collision.h"
#include "GameConfigs.h"

__BEGIN_API

class MainThread
{
public:
    MainThread() {}
    ~MainThread() {}


    static void run(void *name)
    {
        EngineThread = new Thread(windowFunc);
        playerShipThread = new Thread(playerShipFunc);
        collisionThread = new Thread(collisionFunc);

        playerShipThread->join();
        windowThread->join();
        keyboardThread->join();
        collisionThread->join();

        delete playerShipThread;
        delete windowThread;
        delete keyboardThread;
        delete collisionThread;
    }

private:
    static void windowFunc()
    {
        windowObj = new Window(GameConfigs::windowWidth, GameConfigs::windowHeight, GameConfigs::fps);
        windowObj->run();
        delete windowObj;
    }

    static void playerShipFunc()
    {
        playerShipObj = new PlayerShip(SpaceShooter::kBoardObj);
        // Nesse ponto, pela ordem de criação das threads, todos os objetos foram criados, então arrumamos as referências
        windowObj->setPlayerShip(playerShipObj);
        playerShipObj->setWindowReference(windowObj);

        playerShipObj->run();
        // delete playerShipObj;
    }

    static void keyBoardFunc()
    {
        kBoardObj = new Keyboard();
        kBoardObj->run();
        // delete kBoardObj;
    }

    static void collisionFunc()
    {
        collisionObj = new Collision();
        collisionObj->setPlayerShip(playerShipObj);
        collisionObj->setWindow(windowObj);
        playerShipObj->setCollisionReference(collisionObj);
        collisionObj->run();
    }

    static Thread *playerShipThread;
    static Thread *windowThread;
    static Thread *keyboardThread;
    static Thread *collisionThread;

    static PlayerShip *playerShipObj;
    static Window *windowObj;
    static Keyboard *kBoardObj;
    static Collision *collisionObj;
};

__END_API

#endif
