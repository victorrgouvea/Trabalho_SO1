#include "PurpleEnemy.h"

__BEGIN_API

PurpleEnemy::PurpleEnemy(Point point, Vector vector, std::shared_ptr<Sprite> spriteAlive,
                          std::shared_ptr<Sprite> deathSprite) 
{   
    centre = point;
    speed = vector;
    color = al_map_rgb(246, 64, 234);
    size = 20;

    sprite = spriteAlive;
    deathSprite = deathSprite;
    deathSpriteIndex = 0;

    lives = 1;
    alive = true;
    fireSpeed = 50;
    fireDelay = std::make_shared<Timer>(60);
    fireDelay->create();
    fireDelay->startTimer();
}

void PurpleEnemy::hit() {
   lives = lives - 1;
   if (lives < 1)
      alive = false;
}

bool PurpleEnemy::in_bound() {
    return centre.x > -200;
}

PurpleEnemy::~PurpleEnemy() {
}

void PurpleEnemy::draw() {
   if (alive) {
      sprite->draw_tinted(centre, color, 0);
   }
   else {
      if (deathSpriteIndex < 5) {
       //deathAnim();
      }
   }      
}

void PurpleEnemy::fire() {
    if (fireDelay->getCount() > fireSpeed) {
        fireDelay->srsTimer();
        Laser *laser1 = new Laser(centre, color, speed + Vector(-150, 40), false);
        Laser *laser2 = new Laser(centre, color, speed + Vector(-150, -40), false);

        MainThread::gameWindow->addSprite(laser1);
        MainThread::gameWindow->addSprite(laser2);
    }
}


void PurpleEnemy::update(double dt) {
   centre = centre + speed * dt;
				
   if (!in_bound()) {
      alive = false;
      return;
   }
   // check y bound and adjust if out
   if (centre.y > 600 - size && speed.y > 0)  
      speed.reflectY();
   if (centre.y < 0 - size && speed.y < 0)
      speed.reflectY();

    fire();
}

void PurpleEnemy::deathAnim() {
   deathSprite->draw_death_anim(deathSpriteIndex, centre, 0);
   deathSpriteIndex++;
}

__END_API