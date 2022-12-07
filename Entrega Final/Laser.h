#ifndef LASER_H
#define LASER_H

#include <allegro5/allegro.h>

#include "Point.h"
#include "Vector.h"

class Laser {
  public:
   Laser (Point p, ALLEGRO_COLOR c, Vector s);   
   ~Laser();
   Point centre;
   ALLEGRO_COLOR color;
   Vector speed;
   bool live;
   void draw();
   void update(double dt);
   void load_assets() { }
   
  private:
   bool in_bound();
};

#endif