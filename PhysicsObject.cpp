#include <iostream>

// #include "Logging.h"
#include "PhysicsObject.h"

namespace sand
{
// ----------------------------------------------------------------------------
PhysicsObject_t::PhysicsObject_t( Vector2 position_, Vector2 velocity_,
                                  float mass_, ObjectType type_ )
    : position{ position_ }, velocity{ velocity_ }, mass{ mass_ }, type{ type_ }
{
   std::cout << "Created Physics object\n";
}

// ----------------------------------------------------------------------------
void PhysicsObject_t::update( float dt )
{
   velocity =
       Vector2Add( velocity, Vector2Scale( acceleration, dt ) );   // v = a * t
   position =
       Vector2Add( position, Vector2Scale( velocity, dt ) );   // v = s / t
   // Renderer only needs the position and other child class related values depending on render function in child
}



};   // namespace sand
