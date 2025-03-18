#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "PhysicsObject.h"

namespace sand
{
class CollisionManager_t
{
 public:
   void checkCollisions(
       const std::vector<std::unique_ptr<PhysicsObject_t>>& objects,
       float                                                groundY );

 private:
   bool checkCollision( const PhysicsObject_t& obj1,
                        const PhysicsObject_t& obj2 );

   bool checkCircleCircle( const PhysicsObject_t& obj1,
                           const PhysicsObject_t& obj2 );

   bool checkCircleRectangle( const PhysicsObject_t& obj1,
                              const PhysicsObject_t& obj2 );
};
};   // namespace sand

#endif
