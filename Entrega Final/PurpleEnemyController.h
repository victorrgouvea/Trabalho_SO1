#ifndef PURPLE_ENEMIES_CONTROL_H
#define PURPLE_ENEMIES_CONTROL_H

#include <list>
#include <memory>
#include "Sprite.h"
#include "PurpleEnemy.h"
#include "thread.h"
#include "traits.h"
#include "MainThread.h"
#include "Laser.h"

__BEGIN_API

class PurpleEnemyController
{
public:
    PurpleEnemyController();
    ~PurpleEnemyController();
    void run();
    std::list<Enemy *> getShips() { return ships; }
    void removeShip(Enemy* ship) {ships.remove(ship); }
private:
    void loadAssets();
    void createShips();
    void processLoop();
    void handleShips();

    std::list<Enemy *> ships;
    std::shared_ptr<Timer> timerSpawn;
    std::shared_ptr<Sprite> shipSprite;
    std::shared_ptr<Sprite> killAnimSprite;
    int delaySpawn;
};

__END_API

#endif