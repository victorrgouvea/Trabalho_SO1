/**
 * @file Engine.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef ENGINE_H
#define ENGINE_H

#include "Threads/traits.h"
#include "Threads/thread.h"
#include <list>
#include "Point.h"
#include "Projectile.h"
#include "Hittable.h"

__BEGIN_API


class Engine {
   
   public:
      Engine();
      ~Engine();

      void run();
      
   private:

      void playerCollisionCheck();
      void enemyCollisionCheck();
      bool playerHitCheck(Projectile *projectile, Hittable *hittable);
      bool enemyHitCheck();
      void objectsClean();

      bool _finish;

      bool get_finish() { return _finish; }


   
};

/*public:
   Engine();
   ~Engine();
   
   void init();
   void run();
   void draw();
   void update(double dt);

   void gameLoop(float& prevTime);

   act::action input(ALLEGRO_KEYBOARD_STATE&);
   void drawShip(std::shared_ptr<Sprite> sprite, int flags);
   void drawBackground();

   inline int getWidth() const {
      return _displayWidth;
   }
   inline int getHeight() const {
      return _displayHeight;
   }
   inline int getFps() const {
      return _fps;
   }

  private:
   void loadSprites();
   //Checks data of the spaceship
   void checkBoundary();
   void selectShipAnimation();
   std::shared_ptr<Sprite> spaceShip;
   Point centre;        /**< ship position */
    //  ALLEGRO_COLOR color; /**< ship color */   
     // Vector speed;        /**< movement speed in any direction */
     // int row;             /**<row of animation to be played */
      //int col;             /**< column of animation to be played */

      //Background
      //Point bgMid;/**<point used by the background to draw from */
      //Point fgMid;
      //Point fg2Mid;
      //Vector bgSpeed;/**<background movement speed */
      //Vector fgSpeed;
      //std::shared_ptr<Sprite> bg;/**<shared pointer to background animation */
      //std::shared_ptr<Sprite> fg;

      // general game variables
      //int _displayWidth;
      //int _displayHeight;
      //int _fps;
      // allegro objects
      //ALLEGRO_TIMER *_timer;
      //ALLEGRO_EVENT_QUEUE *_eventQueue;
      //ALLEGRO_DISPLAY *_display;

      //bool _finish;
__END_API


#endif
