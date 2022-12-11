/**
 * @file Engine.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef ENGINE_H
#define ENGINE_H

#include "traits.h"
#include "thread.h"
#include <list>
#include "Point.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Player.h"
#include "MainThread.h"
#include <stdio.h>

__BEGIN_API


class Engine {
   
   public:
      Engine();
      ~Engine();
      void checkCollisionOnEnemies() ;
      void checkCollidingEnemyWithPlayer();
      void checkCollisionOnPlayer();
      bool doColorsMatch(const ALLEGRO_COLOR& a, const ALLEGRO_COLOR& b);
      bool isPointBoxCollision(const Point& p1, const Point& p2, const int& s2);
      bool doHitboxesIntersect(const Point& centre1, const int& size1,
				 const Point& centre2, const int& size2);
      void run();
      void addEnemy(Enemy * sprite) {
         enemiesToCheck.push_front(sprite);
      }
      void removeEnemy(Enemy * sprite) {
         enemiesToCheck.remove(sprite);
      }
      void addProj(Projectile * sprite) {
         projToCheck.push_front(sprite);
      }
      void removeProj(Projectile * sprite) {
         projToCheck.remove(sprite);
      }
      void addDeadEnemy(Enemy * sprite) {
         deadEnemies.push_front(sprite);
      }
      void removeDeadEnemy(Enemy * sprite) {
         deadEnemies.remove(sprite);
      }
      void addDeadProj(Projectile * sprite) {
         deadProj.push_front(sprite);
      }
      void removeDeadProj(Projectile * sprite) {
         deadProj.remove(sprite);
      }

   private:
      std::list<Enemy *> enemiesToCheck;
      std::list<Projectile *> projToCheck;
      std::list<Enemy *> deadEnemies;
      std::list<Projectile *> deadProj;
      void spriteCollisionCheck();
      bool hitCheck(Drawable *sprite1, Drawable *sprite2);

};

__END_API


#endif
