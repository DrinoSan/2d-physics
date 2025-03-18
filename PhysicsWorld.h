#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#include <memory>
#include <vector>

#include "Force.h"
#include "PhysicsObject.h"
#include "CollisionManager.h"

namespace sand
{
class PhysicsWorld_t
{
 public:
   PhysicsWorld_t( float ground );

   void addObject( std::unique_ptr<PhysicsObject_t> object );
   void addForce( std::unique_ptr<Force_t> force );
   void update( float dt );
   const std::vector<std::unique_ptr<PhysicsObject_t>>& getObjects() const
   {
      return objects;
   }

   float getGroundY() const { return groundY; }

 private:
   std::vector<std::unique_ptr<PhysicsObject_t>>
                                         objects;   // List of physics objects
   std::vector<std::unique_ptr<Force_t>> forces;    // List of forces
   float                                 groundY;   // Y-position of the ground

   CollisionManager_t collisionManager{};
};
};   // namespace sand

#endif
