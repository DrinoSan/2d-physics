#ifndef FORCE_H
#define FORCE_H

namespace sand
{
class PhysicsObject_t;

class Force_t
{
 public:
   virtual void apply( PhysicsObject_t* obj ) = 0;

   virtual ~Force_t() = default;
};
};   // namespace sand

#endif
