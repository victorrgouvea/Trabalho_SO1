#include "Laser.h"

#include <allegro5/allegro_primitives.h>

__BEGIN_API

Laser::Laser(Point p, ALLEGRO_COLOR c, Vector s)
{  
   centre = p;
   color = c;
   speed =s;
   centre = p + s * 0.1; // so it doesn't hit its own projectile
}

Laser::~Laser() {
   std::cout << "delete do laser\n";
}

void Laser::update(double dt) {
   centre = centre + speed * dt;
    if (!in_bound())
       alive = false;
}
bool Laser::in_bound()
{
	if ((centre.x > MainThread::gameWindow->getWidth()) ||
			(centre.x < 0) ||
			(centre.y > MainThread::gameWindow->getHeight()) ||
			(centre.y < 0))
			return true;
  return false;
};
void Laser::draw() {
   Point tracer = centre + speed * (0.05);  
   al_draw_line(centre.x, centre.y,
		tracer.x, tracer.y,
	  color, 3);
}

__END_API