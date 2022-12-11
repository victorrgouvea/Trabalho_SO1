#include "Engine.h"

__BEGIN_API


Engine::Engine() {}

Engine::~Engine() {}

void Engine::pushEnemiesProj(Projectile *proj) {
   enemiesProj.push_front(proj);
}

void Engine::pushPlayerProj(Projectile *proj) {
   playerProj.push_front(proj);
}

void Engine::run() {
 
   while (MainThread::gameWindow->getGameRunning()) {
      playerCollisionCheck();  // checa se o player foi atingido por alguma coisa
      enemyCollisionCheck();  // checa se algum inimigo foram atingidos pelo player
      Thread::yield();
   }
}

void Engine::playerCollisionCheck() { 
   for (auto proj = enemiesProj.begin(); proj != enemiesProj.end(); proj++)
    {
        Projectile *projectile = *proj;

        if (playerHitCheck(projectile))
        {
            Player *player = MainThread::player;
            GameWindow *gameWindow = MainThread::gameWindow;
            
            player->hit();
            // Destrói o tiro
            gameWindow->removeProjectile(projectile);
            enemiesProj.remove(projectile);
            delete projectile;

            if (!player->alive())
            {
                gameWindow->setGameRunning(true);
                return;
            }
        }
    }
}

void Engine::enemyCollisionCheck() {
   for (auto proj = playerProj.begin(); proj != playerProj.end(); proj++)
    {
        Projectile *projectile = *proj;
        GameWindow *gameWindow = MainThread::gameWindow;

        for (auto item = gameWindow->getEnemyList().begin(); item != gameWindow->getEnemyList().end(); item++)
        {
            Enemy *enemy = *item;


            if (enemyHitCheck(projectile, enemy))
            {
                gameWindow->removeProjectile(projectile);
                playerProj.remove(projectile);
                delete projectile;

                enemy->hit();
                if (enemy->isDead())
                {
                    gameWindow->removeEnemy(enemy);
                    gameWindow->getEnemyList().remove(enemy);
                    //delete enemy;
                }
            }
        }
    }
}

bool Engine::playerHitCheck(Projectile *projectile) {
   Player *player = MainThread::player;
   int tamanhoPlayer = player->getSize();
   Point posicaoProjectile = projectile->getPosition();
   Point posicaoPlayer = player->getPosition();

   if (posicaoProjectile.x > posicaoPlayer.x - tamanhoPlayer &&
        (posicaoProjectile.x < posicaoPlayer.x + tamanhoPlayer) &&
        (posicaoProjectile.y > posicaoPlayer.y - tamanhoPlayer) &&
        (posicaoProjectile.y < posicaoPlayer.y + tamanhoPlayer))
      return true;
   return false;
}

bool Engine::enemyHitCheck(Projectile *projectile, Enemy *enemy) {
   int tamanhoEnemy = enemy->getSize();
   Point posicaoProjectile = projectile->getPosition();
   Point posicaoEnemy = enemy->getPosition();

   if (posicaoProjectile.x > posicaoEnemy.x - tamanhoEnemy &&
        (posicaoProjectile.x < posicaoEnemy.x + tamanhoEnemy) &&
        (posicaoProjectile.y > posicaoEnemy.y - tamanhoEnemy) &&
        (posicaoProjectile.y < posicaoEnemy.y + tamanhoEnemy))
      return true;
   return false;
}

__END_API
