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

// ----------------------------------------------------------------------------
void CircleObject_t::onObjectCollision( PhysicsObject_t& other )
{

   switch ( other.type )
   {
   case ObjectType::Circle:
   {
      // We already know we have a collision so no need to check that here

      // Casting to pointer because references can couse exception while pointer
      // would just return a nullptr
      auto* otherCircle = dynamic_cast<CircleObject_t*>( &other );

      // Circle A, Circle B
      // Getting distance between AB
      auto d = Vector2Distance( position, otherCircle->position );

      // Avoid division by zero if circles are exactly on top of each other.
      // Finding this took wayyyy to long
      Vector2     v;
      const float epsilon = 0.0001f;
      if ( d < epsilon )   // This happens when the circles basically start
                           // inside eachother
      {
         // Whatever direction
         v = { 1.0f, 0.0f };
         d = epsilon;   // d was fucking small
      }
      else
      {
         auto AB = Vector2Subtract( position, otherCircle->position );

         // Getting the unit vector
         v = Vector2Normalize( AB );
      }

      // Getting the collision point, this is not necessary but i want to do it
      // fuck it. Getting distance to the collision point, check:
      // https://mathworld.wolfram.com/Circle-CircleIntersection.html
      auto dSquare  = d * d;
      auto r1Square = radius * radius;
      auto r2Square = otherCircle->radius * otherCircle->radius;
      // Distance
      auto h = ( dSquare + r1Square - r2Square ) / ( 2 * d );

      // Collision Point if no bounce back
      auto M = Vector2Add( position, Vector2Scale( v, h ) );
      std::cout << "Collision point position: (" << M.x << "," << M.y << ")\n";

      // Calculate relative velocity.
      Vector2 relVelocity = Vector2Subtract( otherCircle->velocity, velocity );
      float   velocityAlongNormal = Vector2DotProduct( relVelocity, v );

      // Push the second circle back so they only touch
      // Calculate overlap
      auto p = radius + otherCircle->radius - d;

      // Calculate how much of a pushback is needed we divide by 0.5 because we apply it to both objects
      auto correction = Vector2Scale( v, p * 0.5f );

      // If objects are nearly at rest relative to each other,
      // just separate them without applying an impulse.
      if ( fabs( velocityAlongNormal ) < EPSILON )
      {
         position = Vector2Subtract( position, correction );
         otherCircle->position =
             Vector2Add( otherCircle->position, correction );

         return;
      }

      // Push
      position              = Vector2Subtract( position, correction );
      otherCircle->position = Vector2Add( otherCircle->position, correction );

      // Adding impulse or bounce
      float   e           = 1.0f;   // Fully elastic

      // If moving apart, no bounce needed
      if ( velocityAlongNormal > 0 )
      {
         return;
      }

      float m1      = mass;
      float m2      = otherCircle->mass;
      float impulse = -( 1 + e ) * velocityAlongNormal / ( 1 / m1 + 1 / m2 );

      Vector2 impulseVector = Vector2Scale( v, impulse );
      velocity = Vector2Add( velocity, Vector2Scale( impulseVector, 1 / m1 ) );
      otherCircle->velocity = Vector2Subtract(
          otherCircle->velocity, Vector2Scale( impulseVector, 1 / m2 ) );

      break;
   }
   };
}

};   // namespace sand
