#ifndef GRAVITY_FORCE_H
#define GRAVITY_FORCE_H

#include "Force.h"
#include "PhysicsObject.h"

namespace sand
{
class GravityForce_t : public Force_t
{
 public:
   GravityForce_t( float gravity_ ) : gravity{ gravity_ } {}
   void apply( PhysicsObject_t& obj ) override
   {
      //obj.acceleration = { obj.acceleration.x, obj.acceleration.y + gravity };
      obj.acceleration.y += gravity;
   }


 private:
   float gravity;   // Acceleration due to gravity (pixels/s^2)
};
};   // namespace sand

#endif
