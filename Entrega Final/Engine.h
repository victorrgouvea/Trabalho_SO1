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

      void run();
      void pushEnemiesProj(Drawable *proj);
      void pushPlayerProj(Drawable *proj);
      void removeEnemiesProj(Drawable *proj) { enemiesProj.remove(proj); }
      void removePlayerProj(Drawable *proj) { playerProj.remove(proj); }
      
   private:

      void playerCollisionCheck();
      void enemyCollisionCheck();
      bool playerHitCheck(Drawable *projectile);
      bool enemyHitCheck(Drawable *projectile, Drawable *enemy);


      // Listas que armazenam os projeteis
      std::list<Drawable *> enemiesProj;
      std::list<Drawable *> playerProj;


   
};

__END_API


#endif
