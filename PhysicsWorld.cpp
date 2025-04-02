#include <assert.h>
#include <iostream>
#include <unistd.h>

#include "PhysicsWorld.h"

namespace sand
{
// ----------------------------------------------------------------------------
PhysicsWorld_t::PhysicsWorld_t( float ground, bool hasSideBorder_ )
    : groundY( ground ), hasSideBorder{ hasSideBorder_ }
{
   std::cout << "Created Physical World\n";

   // If hasSideBorder is set but no value i will just use defaults
   distanceFromCenter = ( GetScreenWidth() / 2 );
   leftBorder         = distanceFromCenter - distanceFromCenter + 10;
   rightBorder        = distanceFromCenter + distanceFromCenter - 10;
}

// ----------------------------------------------------------------------------
PhysicsWorld_t::PhysicsWorld_t( float ground, float distanceFromCenter_,
                                bool hasSideBorder_ )
    : groundY( ground ), distanceFromCenter{ distanceFromCenter_ },
      hasSideBorder{ hasSideBorder_ }
{
   std::cout << "Created Physical World\n";
}

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
   if ( isGravityActivated == true )
   {
      for ( auto& obj : objects )
      {
         // Reset acceleration so we dont carry it from previous frames...
         obj->acceleration = { 0.0f, 0.0f };

         for ( auto& force : forces )
         {
            force->apply( obj.get() );
         }
      }
   }

   for ( auto& obj : objects )
   {
      obj->update( dt, isGravityActivated );
   }

   collisionManager.checkCollisions( objects, groundY, leftBorder, rightBorder,
                                     isGravityActivated );
}

};   // namespace sand
