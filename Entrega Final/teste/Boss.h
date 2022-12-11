#ifndef BOSS_H
#define BOSS_H

#include <list>
#include <memory>
#include "thread.h"
#include "traits.h"

#include "Enemy.h"
#include "Timer.h"
#include "Sprite.h"
#include "Point.h"
#include "Vector.h"

__BEGIN_API

class Boss : public Enemy
{
public:
    Boss(Point point, Vector vector, std::shared_ptr<Sprite> bossSprite);


    void run();
    bool canFire() { return this->_canFire; }
    void draw();
    void attack();
    void loadAssets();
    void update(double diffTime);
    void hit(int damage);
    bool isOutside();
    bool isDead();
    ALLEGRO_COLOR getColor() { return this->color; }
    int getSize() { return size; };
    void updateFrame();

private:
    Point point;
    Vector vector;
    std::shared_ptr<Timer> projectilesTimer;
    std::shared_ptr<Timer> spawnTimer;
    std::shared_ptr<Sprite> bossSprites;
    int spriteSheetIndex;
    ALLEGRO_COLOR color;
    int row;
    int col;
    int size;
    int shotSpeed;
    int lifes;
    int baseHp;
    bool canFire;
    bool targatable;
};

__END_API

#endif