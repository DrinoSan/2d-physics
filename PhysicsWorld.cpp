#include <iostream>

#include "CollisionManager.h"
#include "PhysicsWorld.h"

namespace sand
{
// ----------------------------------------------------------------------------
PhysicsWorld_t::PhysicsWorld_t( float ground ) : groundY( ground ) {}

// ----------------------------------------------------------------------------
void PhysicsWorld_t::addObject( std::unique_ptr<PhysicsObject_t> obj )
{
   objects.push_back( std::move( obj ) );
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
      for ( auto& force : forces )
      {
         force->apply( obj.get() );
      }

      obj->update( dt );

      // Reset acceleration so we dont carry it from previous frames...
      obj->acceleration = { 0.0f, 0.0f };

      collisionManager.checkCollisions( objects, groundY );
   }
}

};   // namespace sand
