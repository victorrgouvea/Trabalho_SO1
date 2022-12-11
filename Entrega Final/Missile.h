/**
 * @file Missile.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef MISSILE_H
#define MISSILE_H

#include <allegro5/allegro.h>

#include <memory>
#include <vector>
#include "MainThread.h"
#include "Point.h"
#include "Vector.h"
#include "Projectile.h"
#include "Sprite.h"
#include "traits.h"

__BEGIN_API

class Missile : public Projectile {   
  public:
   Missile(Point p, ALLEGRO_COLOR c, Vector s, bool isPlayerShot);
   ~Missile();
   Point centre;
   ALLEGRO_COLOR color;
   Vector speed;
   bool live;
   void draw();
   void update(double dt);
   void loadSprites();
   bool isOutside();
   Point getPosition() { return centre; }
	 int getSize() { return 16; } 
   double angle;
   std::vector<std::shared_ptr<Sprite>> sprites;
   int currentSpriteIndex;
};

__END_API

#endif