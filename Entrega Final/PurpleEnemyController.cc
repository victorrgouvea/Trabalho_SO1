#include "PurpleEnemyController.h"

__BEGIN_API

PurpleEnemyController::PurpleEnemyController()
{
    loadAssets();
    delaySpawn = 250;
    timerSpawn = std::make_shared<Timer>(60);
    timerSpawn->create();
    timerSpawn->startTimer();
}

PurpleEnemyController::~PurpleEnemyController() {}

void PurpleEnemyController::run()
{
    loadAssets();
    while (MainThread::gameWindow->getGameRunning())
    {
        if (MainThread::gameWindow == nullptr || MainThread::engine == nullptr)
        {
            Thread::yield();
        } else {
            if (timerSpawn->getCount() > delaySpawn) {
                createShips();
            }
            handleShips();
            Thread::yield();
        }
    }
}

void PurpleEnemyController::loadAssets()
{
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    shipSprite = std::make_shared<Sprite>("EnemyBasic.png");
    killAnimSprite = std::make_shared<Sprite>("explode.png");
    al_destroy_path(path);
}

void PurpleEnemyController::handleShips()
{
    for (auto item = ships.begin(); item != ships.end(); item++)
    {
        PurpleEnemy *ship = *item;
        ship->fire();
    }
}

void PurpleEnemyController::createShips()
{
    PurpleEnemy *purpleEnemy1 = new PurpleEnemy(Point(800, 300), Vector(-180, 0), shipSprite, killAnimSprite);
    PurpleEnemy *purpleEnemy2 = new PurpleEnemy(Point(900, 350), Vector(-180, 0), shipSprite, killAnimSprite);
    PurpleEnemy *purpleEnemy3 = new PurpleEnemy(Point(900, 250), Vector(-180, 0), shipSprite, killAnimSprite);
    PurpleEnemy *purpleEnemy4 = new PurpleEnemy(Point(1000, 400), Vector(-180, 0), shipSprite, killAnimSprite);
    PurpleEnemy *purpleEnemy5 = new PurpleEnemy(Point(1000, 200), Vector(-180, 0), shipSprite, killAnimSprite);
    PurpleEnemy *purpleEnemy6 = new PurpleEnemy(Point(1100, 100), Vector(-180, 0), shipSprite, killAnimSprite);
    PurpleEnemy *purpleEnemy7 = new PurpleEnemy(Point(1100, 500), Vector(-180, 0), shipSprite, killAnimSprite);
    ships.push_front(purpleEnemy1);
    ships.push_front(purpleEnemy2);
    ships.push_front(purpleEnemy3);
    ships.push_front(purpleEnemy4);
    ships.push_front(purpleEnemy5);
    ships.push_front(purpleEnemy6);
    ships.push_front(purpleEnemy7);
    MainThread::engine->addEnemy(purpleEnemy1);
    MainThread::engine->addEnemy(purpleEnemy2);
    MainThread::engine->addEnemy(purpleEnemy3);
    MainThread::engine->addEnemy(purpleEnemy4);
    MainThread::engine->addEnemy(purpleEnemy5);
    MainThread::engine->addEnemy(purpleEnemy6);
    MainThread::engine->addEnemy(purpleEnemy7);
    MainThread::gameWindow->addSprite(purpleEnemy1);
    MainThread::gameWindow->addSprite(purpleEnemy2);
    MainThread::gameWindow->addSprite(purpleEnemy3);
    MainThread::gameWindow->addSprite(purpleEnemy4);
    MainThread::gameWindow->addSprite(purpleEnemy5);
    MainThread::gameWindow->addSprite(purpleEnemy6);
    MainThread::gameWindow->addSprite(purpleEnemy7);


    timerSpawn->srsTimer();
}

__END_API