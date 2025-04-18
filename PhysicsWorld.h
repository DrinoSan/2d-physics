#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#include <memory>
#include <vector>

#include "CollisionManager.h"
#include "Force.h"
#include "PhysicsObject.h"

namespace sand
{
class PhysicsWorld_t
{
 public:
   PhysicsWorld_t( float ground, bool hasSideBorder_ = false );
   PhysicsWorld_t( float ground, float distanceFromCenter_,
                   bool hasSideBorder_ = false );

   void addObject( std::unique_ptr<PhysicsObject_t> object );
   void addForce( std::unique_ptr<Force_t> force );
   void update( float dt );
   const std::vector<std::unique_ptr<PhysicsObject_t>>& getObjects() const
   {
      return objects;
   }

   float groundY;              // Y-position of the ground
   float distanceFromCenter;   // I only use symentrical borders...
   float leftBorder;           // I only use symentrical borders...
   float rightBorder;          // I only use symentrical borders...
   bool  hasSideBorder;
   bool  isGravityActivated;

 private:
   std::vector<std::unique_ptr<PhysicsObject_t>>
                                         objects;   // List of physics objects
   std::vector<std::unique_ptr<Force_t>> forces;    // List of forces

   CollisionManager_t collisionManager{};
};
};   // namespace sand

#endif
