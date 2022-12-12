#include "Engine.h"

__BEGIN_API


Engine::Engine() {}

Engine::~Engine() {}

void Engine::pushEnemiesProj(Drawable *proj) {
   enemiesProj.push_front(proj);
}

void Engine::pushPlayerProj(Drawable *proj) {
   playerProj.push_front(proj);
}

void Engine::pushEnemies(Enemy *enem) {
   enemies.push_front(enem);
}

void Engine::run() {
 
   while (MainThread::gameWindow->getGameRunning()) {
      playerCollisionCheck();  // checa se o player foi atingido por alguma coisa
      enemyCollisionCheck();
      Thread::yield();
   }
}

void Engine::playerCollisionCheck() { 
   for (auto proj = enemiesProj.begin(); proj != enemiesProj.end(); )
    {
        Drawable *projectile = *proj;
        proj++;
        if (playerHitCheck(projectile))
        {
            Player *player = MainThread::player;
            GameWindow *gameWindow = MainThread::gameWindow;
            
            player->hit();
            gameWindow->removeProjectile(projectile);
            enemiesProj.remove(projectile);

            if (!player->getAlive())
            {
                gameWindow->setGameRunning(false);
                return;
            }
        }
    }
}

void Engine::enemyCollisionCheck() {

    GameWindow *gameWindow = MainThread::gameWindow;
    for (auto proj = playerProj.begin(); proj != playerProj.end();)
    {
        Drawable *projectile = *proj;
        proj++;

        for (auto item = enemies.begin(); item != enemies.end();)
        {
            Enemy *enemy = *item;
            item++;
            
            if (enemyHitCheck(projectile, enemy))
            {
                gameWindow->removeProjectile(projectile);
                playerProj.remove(projectile);
                enemy->hit();
                if (!enemy->getAlive())
                {
                    MainThread::purpleEnemy->removeShip(enemy);
                    removeEnemies(enemy);
                    gameWindow->removeEnemy(enemy);
                }
            }
        }
    }
}

bool Engine::playerHitCheck(Drawable *projectile) {
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

bool Engine::enemyHitCheck(Drawable *projectile, Enemy *enemy) {
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
