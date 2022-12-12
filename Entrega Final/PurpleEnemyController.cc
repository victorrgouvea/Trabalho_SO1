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
                this->createShips();
            }
            this->handleShips();
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
    for (auto item = this->ships.begin(); item != this->ships.end(); item++)
    {
        Enemy *ship = *item;
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
    MainThread::engine->pushEnemies(purpleEnemy1);
    MainThread::engine->pushEnemies(purpleEnemy2);
    MainThread::engine->pushEnemies(purpleEnemy3);
    MainThread::engine->pushEnemies(purpleEnemy4);
    MainThread::engine->pushEnemies(purpleEnemy5);
    MainThread::engine->pushEnemies(purpleEnemy6);
    MainThread::engine->pushEnemies(purpleEnemy7);
    MainThread::gameWindow->addEnemy(purpleEnemy1);
    MainThread::gameWindow->addEnemy(purpleEnemy2);
    MainThread::gameWindow->addEnemy(purpleEnemy3);
    MainThread::gameWindow->addEnemy(purpleEnemy4);
    MainThread::gameWindow->addEnemy(purpleEnemy5);
    MainThread::gameWindow->addEnemy(purpleEnemy6);
    MainThread::gameWindow->addEnemy(purpleEnemy7);


    timerSpawn->srsTimer();
}



__END_API