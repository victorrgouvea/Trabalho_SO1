#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <allegro5/allegro.h> // for color
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include "Point.h"
#include "Vector.h"
#include "Drawable.h"
#include "Updateable.h"
#include "traits.h"

__BEGIN_API

class Projectile : public Drawable {
  public:
   
   Projectile(Point p, ALLEGRO_COLOR c, Vector s) : centre(p), color(c), speed(s)
   {
      live = true;
   }

   virtual ~Projectile() { }

   virtual void load_assets() = 0;
   
   virtual void draw() = 0;
   virtual void update(double diffTime) = 0;
   virtual bool isOutside() = 0;
   virtual int getSize() = 0;
   virtual Point getPosition() = 0;

   private:
      Point centre;
      ALLEGRO_COLOR color;
      Vector speed;
      bool live;
   
};

__END_API

#endif