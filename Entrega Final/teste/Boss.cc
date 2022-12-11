#include "Boss.h"

__BEGIN_API


Boss::Boss(Point pointR, Vector vectorR, std::shared_ptr<Sprite> bossSprite)
{
    point = pointR;
    vector = vectorR;
    bossSprites = bossSprite;
    color = al_map_rgb(0, 0, 0);

    projectilesTimer = std::make_shared<Timer>(60);
    projectilesTimer->create();
    projectilesTimer->startTimer();

    baseHp = 50;
    lifes = 30;

    spawnTimer = std::make_shared<Timer>(60);
    spawnTimer->create();
    spawnTimer->startTimer();

    row = 0;
    col = 0;
    spriteSheetIndex = 0;
    size = 80;
    targatable = false;
}

void Boss::hit(int damage)
{
    
}

void Boss::draw()
{
    updateFrame();

}

void Boss::attack() {}

bool Boss::isOutside() { return false; }

void Boss::update(double diffTime)
{
    point = point + vector * diffTime;

    if (point.x < 700 && !targatable)
    {
        targatable = true;
        vector.x = 0;
        vector.y = 100;
    }

    if (point.y > 450 && vector.y > 0)
        vector.reflectY();

    if (point.y < 150 && vector.y < 0)
        vector.reflectY();

    if (projectilesTimer->getCount() > shotSpeed)
    {
        canFire = true;
        projectilesTimer->srsTimer();
    }
}

bool Boss::isDead() { return lifes <= 0; }

void Boss::updateFrame()
{
    if (lifes > baseHp)
        spriteSheetIndex = 0;

    if (lifes <= baseHp && spriteSheetIndex < 3)
    {
        shotSpeed = rand() % 50 + 20;
        vector = vector * 1.1;
        size = 70;
        spriteSheetIndex++;
    }
    // final damage animation-- fire speed up again
    if (lifes <= 20 && spriteSheetIndex < 8)
    {
        shotSpeed = rand() % 30 + 20;
        vector = vector * 1.1;
        size = 60;
        spriteSheetIndex++;
    }
    // interpret index as row and col of sprite sheet
    row = spriteSheetIndex / 3;
    col = spriteSheetIndex % 3;
}

__END_API