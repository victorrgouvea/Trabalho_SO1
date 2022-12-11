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
    Boss(Point point, Vector vector, std::shared_ptr<Sprite> bossSprites);

    void run();
    bool canFire() { return this->_canFire; }
    void draw();
    void attack();
    void update(double diffTime);
    void hit(int damage);
    bool isOutside();
    bool isDead();
    ALLEGRO_COLOR getColor() { return this->color; }
    int getSize();

private:
    static int BOSS_LIFE;

    // Logic
    bool _canFire;
    void updateSprite();
    int life;
    int fireSpeed;
    int size;
    bool invincible;
    int spritesIndex;
    std::shared_ptr<Timer> shotsTimer;
    std::shared_ptr<Sprite> bossSprites;
    ALLEGRO_COLOR color;
    int row;
    int col;
};

__END_API

#endif