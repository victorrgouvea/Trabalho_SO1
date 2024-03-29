#ifndef UPDATEABLE_H
#define UPDATEABLE_H

/**
 * @class Updateable
 * @brief interface for updateable objects
 *
 * provides the declaration of the update function
 */

#include "traits.h"

__BEGIN_API

class Updateable {
  public:
   /**
    * @fn virtual void update(double)
    * @brief virtual function declaration of update, updates the position of derived objects
    * @param t the change in time since the last position update
    */
   virtual ~Updateable() {}
   virtual void update(double t) = 0;


   /**
    * @fn virtual void inBound()
    * @brief returns true if the object is within the display boundaries, false otherwise
    */
   //virtual bool inBound() = 0;
};

__END_API

#endif