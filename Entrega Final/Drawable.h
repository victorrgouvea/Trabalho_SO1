#ifndef DRAWABLE_H
#define DRAWABLE_H

/**
 * @class Drawable
 * @brief interface for drawable objects
 *
 * provides the declaration of the draw function
 */
#include "Point.h"
#include "traits.h"
#include <string.h>

__BEGIN_API

class Drawable {
  public:
   /**
    * @fn virtual void draw()
    * @brief virtual function to draw derived objects
    */ 
  virtual void hit () = 0;
  virtual bool getAlive() = 0;
  virtual void draw() = 0;
  virtual void update(double diffTime) = 0;
  virtual bool in_bound() = 0;
  virtual int getSize() = 0;
  virtual Point getPosition() = 0;
  virtual std::string classType() = 0;
  ALLEGRO_COLOR color;
};

__END_API

#endif