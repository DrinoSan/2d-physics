#include "CircleObject.h"
#include <assert.h>

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
   if ( velocity.y > 3.0f )
   {
      velocity.y = -velocity.y * 0.7f;   // Reverse with factor
   }
   else
   {
      velocity.y = 0.0f;   // Stop the ball, but will again be changes after gravity hits and then the collision will be checked and so on
      // To be more precise gravity will change the accelration field and physicObject::update will change the velocity
   }

   position.y = groundY - radius;   // Always correct position so it does not fall under the line
}

// ----------------------------------------------------------------------------
void CircleObject_t::onObjectCollision( PhysicsObject_t& other )
{
   // Check if the other object is a circle
   CircleObject_t* otherCircle = dynamic_cast<CircleObject_t*>( &other );

   // For all the math:
   // https://mathworld.wolfram.com/Circle-CircleIntersection.html

   // Calculate the distance between the centers of the two circles
   float d = Vector2Distance( position, otherCircle->position );

   Vector2     v;
   const float epsilon = 0.0001f;
   if ( d < epsilon )   // Das ist nur notwendig wenn sie quasi ineinander
                        // starten also fucking klein
   {
      v = { 1.0f, 0.0f };   // Default direction... TODO: randomize this
      d = epsilon;
   }
   else
   {
      Vector2 AB = Vector2Subtract( otherCircle->position, position );
      v          = Vector2Normalize( AB );
   }

   float overlap = radius + otherCircle->radius - d;

   /////// NOT NEEDED BUT I WANT TO HAVE IT
   auto overlapSquare = overlap * overlap;
   auto r1Square      = radius * radius;
   auto r2Square      = otherCircle->radius * otherCircle->radius;
   auto h = ( overlapSquare + r1Square - r2Square ) / ( 2 * overlap );
   auto M = Vector2Add( position, Vector2Scale( v, h ) );
   std::cout << "Collision point position: (" << M.x << "," << M.y << ")\n";
   ////////////////////////////////////////

   Vector2 correction = Vector2Scale(
       v, overlap * 0.5f );   // 0.5 because i update both objects here

   position = Vector2Subtract(
       position, correction );   // Subtract weil v in B richtung zeigt daher OP
                                 // = OP - v damit wir weg von B gehen
   otherCircle->position = Vector2Add(
       otherCircle->position,
       correction );   // Add weil wir jezt uns weg von A bewegen wollen aber v
                       // in richtung a schaut daher OP = OP + v damit wir in
                       // die richung weiter gehen wohin v zeigt also von A nach
                       // B

   Vector2 relVelocity =
       Vector2Subtract( velocity, otherCircle->velocity );   // v1 - v2

   float velocityAlongNormal = Vector2DotProduct( relVelocity, v );
   if ( velocityAlongNormal > 0 )
   {
      float e  = 0.8f;
      float m1 = mass;
      float m2 = otherCircle->mass;
      float j  = -( 1 + e ) * velocityAlongNormal / ( 1 / m1 + 1 / m2 );

      Vector2 impulse = Vector2Scale( v, j );

      std::cout << "Before: this " << velocity.y << ", other "
                << otherCircle->velocity.y << "\n";
      velocity = Vector2Add( velocity, Vector2Scale( impulse, 1 / m1 ) );
      otherCircle->velocity = Vector2Subtract(
          otherCircle->velocity, Vector2Scale( impulse, 1 / m2 ) );

      std::cout << "After: this " << velocity.y << "\n";
   }

   // If nearly at no movement is there make them stop
   const float restThreshold = 0.01f;
   if ( fabs( velocityAlongNormal ) < epsilon )
   {
      velocity = Vector2Scale( velocity, 0.5f );
      if ( Vector2Length( velocity ) < restThreshold )
      {
         velocity = { 0.0f, 0.0f };
      }

      return;
   }
}

};   // namespace sand
