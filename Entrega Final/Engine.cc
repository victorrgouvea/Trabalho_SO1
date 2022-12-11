#include "Engine.h"

__BEGIN_API


Engine::Engine() {}

Engine::~Engine() {}

void Engine::run() {
 
   while (MainThread::gameWindow->getGameRunning()) {
      spriteCollisionCheck();  // checa se o player foi atingido por alguma coisa
      Thread::yield();
   }
}
/*
void Engine::spriteCollisionCheck() { 
    GameWindow *gameWindow = MainThread::gameWindow;
    for (auto proj = spritesToCheck.begin(); proj != spritesToCheck.end();)
    {
        Drawable *sprite1 = *proj;
        proj++;
        if (sprite1->classType() == "proj") {
            for (auto proj2 = spritesToCheck.begin(); proj2 != spritesToCheck.end();)
            {
                Drawable *sprite2 = *proj2;
                proj2++;
                if (sprite1 != sprite2) {
                    if (hitCheck(sprite1, sprite2))
                    {   
                        sprite1->hit();
                        sprite2->hit();
                        if (!sprite1->getAlive()) {
                            removeSprite(sprite1);
                            gameWindow->removeSprite(sprite1);
                            delete sprite1;
                        }
                        if (!sprite2->getAlive()) {
                            removeSprite(sprite2);
                            gameWindow->removeSprite(sprite2);
                            delete sprite2;
                        }
                    }
                } else if (hitCheck(sprite2, sprite1)) {
                    sprite1->hit();
                        sprite2->hit();
                        if (!sprite1->getAlive()) {
                           
                            delete sprite1;
                        }
                        if (!sprite2->getAlive()) {
                            removeSprite(sprite2);
                            gameWindow->removeSprite(sprite2);
                            delete sprite2;
                        }
                }
            }
        }
    }
}
*/

void Engine::spriteCollisionCheck() { 
    GameWindow* gamewindow = MainThread::gameWindow;
   checkCollisionOnPlayer();
   checkCollisionOnEnemies();
   checkCollidingEnemyWithPlayer();
   for (auto it = deadEnemies.begin(); it != deadEnemies.end();) {	
        removeEnemy(*it);
        gamewindow->removeSprite(*it);
        auto *holder = *it;
        it++;
        removeDeadEnemy(holder);
   }
   for (auto it = deadProj.begin(); it != deadProj.end();) {	
        removeProj(*it);
        gamewindow->removeSprite(*it);
        auto *holder = *it;
        it++;
        removeDeadProj(holder);
   }
}
void Engine::checkCollidingEnemyWithPlayer() {
   if (!enemiesToCheck.empty() && (MainThread::player != nullptr)) {      
      for (auto it = enemiesToCheck.begin(); it != enemiesToCheck.end(); ++it) {	 
	 if ((*it)->getAlive() == false) {	    
	    if (doHitboxesIntersect(MainThread::player->getPosition(), MainThread::player->getSize(), (*it)->getPosition(), 
				    (*it)->getSize())) {
	       // collision - register damage
	       (*it)->hit();
	       MainThread::player->hit();
	    }
	 }	       
      }
   }  
}


void Engine::checkCollisionOnPlayer() {
   if (!projToCheck.empty() && (MainThread::player != nullptr)) {
      for (auto it = projToCheck.begin(); it != projToCheck.end(); ++it) {	    
	 // check if projectile color is different from player color
	 if (!doColorsMatch((*it)->color, MainThread::player->color)) {
	    if (isPointBoxCollision((*it)->getPosition(), MainThread::player->getPosition(), MainThread::player->getSize())) {	  
	       // register damage on player and flag projectile as dead
           std::cout << "acertou \n";
	       (*it)->hit();
           if ((*it)->getAlive()) {
            addDeadProj(*it);
          }
	       MainThread::player->hit();
	    }
	 }
      }
   }  
}

bool Engine::doHitboxesIntersect(const Point& centre1, const int& size1,
				 const Point& centre2, const int& size2) {
   return (abs(centre1.x - centre2.x) < (size1 + size2) &&
	   abs(centre1.y - centre2.y) < (size1 + size2));
}


bool Engine::isPointBoxCollision(const Point& p1, const Point& p2, 
				 const int& s2) {
   return ((p1.x > p2.x - s2) &&
	   (p1.x < p2.x + s2) &&
	   (p1.y > p2.y - s2) &&
	   (p1.y < p2.y + s2));
}

void Engine::checkCollisionOnEnemies() {
   if (!projToCheck.empty() && !enemiesToCheck.empty() && (MainThread::player != nullptr)) {
      // set player color for which we will be checking for
      for (auto it_proj = projToCheck.begin(); it_proj != projToCheck.end(); ++it_proj) {
        // check if colors match
        if (doColorsMatch(MainThread::player->color, (*it_proj)->color)) {
            for (auto it_enem = enemiesToCheck.begin(); it_enem != enemiesToCheck.end(); ++it_enem)  {
            
            // set bounding points
            Point pt_proj = (*it_proj)->getPosition();
            Point pt_enem = (*it_enem)->getPosition();
            int enem_size = (*it_enem)->getSize();

	       // check for collision
	       if ((pt_proj.x > pt_enem.x - enem_size) &&
		   (pt_proj.x < pt_enem.x + enem_size) &&
		   (pt_proj.y > pt_enem.y - enem_size) &&
		   (pt_proj.y < pt_enem.y + enem_size)) {
		     
		  // register damage on enemy and flag projectile as dead
		  (*it_proj)->hit();
		  (*it_enem)->hit();
		     
		  // check for enemy death, update score if true
		  if ((*it_enem)->getAlive()) {
		     addDeadEnemy(*it_enem);
		  }
          if ((*it_proj)->getAlive()) {
            addDeadProj(*it_proj);
          }
           }
	    }
	 }
      }
   }
}

bool Engine::doColorsMatch(const ALLEGRO_COLOR& a, const ALLEGRO_COLOR& b) {
   return (a.r == b.r && a.g == b.g && a.b == b.b);
}
__END_API
