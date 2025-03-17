#include <iostream>

#include "PhysicsWorld.h"

namespace sand
{
// ----------------------------------------------------------------------------
PhysicsWorld_t::PhysicsWorld_t( float ground ) : groundY( ground ) {}

// ----------------------------------------------------------------------------
void PhysicsWorld_t::addObject( PhysicsObject_t& obj )
{
   objects.push_back( obj );
}

// ----------------------------------------------------------------------------
void PhysicsWorld_t::addForce( std::unique_ptr<Force_t> force )
{
   forces.push_back( std::move( force ) );
}

// ----------------------------------------------------------------------------
void PhysicsWorld_t::update( float dt )
{
   // Updating all objects
   for ( auto& obj : objects )
   {
      // Reset acceleration so we dont carry it from previous frames...
      obj.acceleration = { 0.0f, 0.0f };

      for ( auto& force : forces )
      {
         force->apply( obj );
      }

      obj.velocity = Vector2Add(
          obj.velocity, Vector2Scale( obj.acceleration, dt ) );   // v = a * t
      obj.position = Vector2Add(
          obj.position, Vector2Scale( obj.velocity, dt ) );   // v = s / t

      std::cout << "-------------- " << obj.position.x << " " << obj.position.y
                << " " << obj.acceleration.y << "\n";
      std::cout << "+++++++ " << obj.velocity.y << "\n";

      // Check collision with ground
      if ( obj.position.y + obj.radius > groundY && obj.velocity.y > 0 )
      {
         if ( obj.velocity.y > 0.5f )
         {
            obj.velocity.y = -obj.velocity.y * 0.7f;   // Reverse with factor
         }
         else
         {
            obj.velocity.y = 0.0f;   // Stop the ball
         }
         obj.position.y = groundY - obj.radius;   // Always correct position
      }
   }
}

};   // namespace sand
