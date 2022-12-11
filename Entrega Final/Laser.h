#ifndef LASER_H
#define LASER_H

#include <allegro5/allegro.h>

#include "thread.h"
#include "traits.h"

#include "Player.h"
#include "GameInput.h"
#include "Sprite.h"
#include "Vector.h"
#include "Drawable.h"
#include "Enemy.h"
#include "Projectile.h"

__BEGIN_API

class Laser: public Projectile {
  public:
   Laser (Point p, ALLEGRO_COLOR c, Vector s);   
   ~Laser();
   Point centre;
   ALLEGRO_COLOR color;
   Vector speed;
   void draw();
   void update(double dt);
   void load_assets() { }
   bool in_bound();
   bool getAlive() { return alive; }
   Point getPosition() { return centre; }
	 int getSize() { return 16; } 
   void hit() {};

  private:
   bool alive;
  std::shared_ptr<Sprite> sprite;
};

__END_API

#endif