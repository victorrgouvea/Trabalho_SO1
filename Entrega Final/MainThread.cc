#include "MainThread.h"


__BEGIN_API

Thread *MainThread::playerT;
Thread *MainThread::windowT;
Thread *MainThread::inputT;
Thread *MainThread::engineT; 
Player *MainThread::player;
GameWindow * MainThread::gameWindow;
GameInput *MainThread::gamekeyb;
Engine *MainThread::engine;

void MainThread::windowInit()
{
    gameWindow = new GameWindow(800, 600, 60);
    gameWindow->run();
    delete gameWindow;
}

void MainThread::playerInit()
{
    player = new Player();
    player->run();
    delete player;
}

void MainThread::inputInit()
{
    gamekeyb = new GameInput();
    gamekeyb->run();
    delete gamekeyb;
}

void MainThread::engineInit()
{
    engine = new Engine();
    engine->run();
    delete engine;
}

__END_API