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

__BEGIN_API


class Engine {
   
   public:
      Engine();
      ~Engine();

      void run();
      void pushEnemiesProj(Projectile *proj);
      void pushPlayerProj(Projectile *proj);

      
   private:

      void playerCollisionCheck();
      void enemyCollisionCheck();
      bool playerHitCheck(Projectile *projectile);
      bool enemyHitCheck(Projectile *projectile, Enemy *enemy);


      // Listas que armazenam os projeteis que tocaram o jogador ou algum inimigo
      std::list<Projectile *> enemiesProj;
      std::list<Projectile *> playerProj;


   
};

__END_API


#endif
