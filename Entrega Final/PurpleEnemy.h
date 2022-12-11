#ifndef PURPLE_ENEMY_H
#define PURPLE_ENEMY_H

#include <memory>
#include "thread.h"
#include "traits.h"
#include "Vector.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Timer.h"
#include "MainThread.h"
#include "Laser.h"

__BEGIN_API

class PurpleEnemy : public Enemy
{
public:
    PurpleEnemy(Point point, Vector vector, std::shared_ptr<Sprite> spriteAlive,
                 std::shared_ptr<Sprite> deathSprite);
    ~PurpleEnemy();
    ALLEGRO_COLOR color;
    Point centre;
    Vector speed;
    void draw();
    void update(double diffTime);
    bool in_bound();
    ALLEGRO_COLOR getColor() { return color; }
    int getSize() { return size; }
    void deathAnim();
    void hit();
    bool getAlive() { return alive;}
    void setAlive(bool estado) { alive = estado; }
    void fire();
    void kill() {};
    Point getPosition() { return centre; }

private:
    // Logic
    int fireSpeed;
    bool alive;
    std::shared_ptr<Timer> fireDelay;
    int size;
    int lives;
    std::shared_ptr<Sprite> sprite;
    std::shared_ptr<Sprite> deathSprite;
    int deathSpriteIndex;
};

__END_API

#endif