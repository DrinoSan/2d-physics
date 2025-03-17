#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#include <vector>
#include <memory>

#include "Force.h"
#include "PhysicsObject.h"

namespace sand
{
class PhysicsWorld_t
{
 public:
   PhysicsWorld_t( float ground );

   void                                addObject( PhysicsObject_t& object );
   void                                addForce( std::unique_ptr<Force_t> force );
   void                                update( float dt );
   const std::vector<PhysicsObject_t>& getObjects() const { return objects; }
   float                               getGroundY() const { return groundY; }

 private:
   std::vector<PhysicsObject_t>          objects;   // List of physics objects
   std::vector<std::unique_ptr<Force_t>> forces;    // List of forces
   float                                 groundY;   // Y-position of the ground
};
};   // namespace sand

#endif
