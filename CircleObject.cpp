#include "CircleObject.h"

namespace sand
{
// ----------------------------------------------------------------------------
void CircleObject_t::update( float dt )
{
   PhysicsObject_t::update( dt );
}

// ----------------------------------------------------------------------------
void CircleObject_t::onGroundCollision( float groundY )
{
   // Check collision with ground
   if ( velocity.y > 0.5f )
   {
      velocity.y = -velocity.y * 0.7f;   // Reverse with factor
   }
   else
   {
      velocity.y = 0.0f;   // Stop the ball
   }

   // Basic update to make sure the object does not fall under the ground
   position.y = groundY - radius;   // Always correct position
}

};   // namespace sand
