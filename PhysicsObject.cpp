#include <iostream>

// #include "Logging.h"
#include "PhysicsObject.h"

namespace sand
{
PhysicsObject_t::PhysicsObject_t( Vector2 position_, Vector2 velocity_,
                                  float mass_, float radius_ )
    : position{ position_ }, velocity{ velocity_ }, mass{ mass_ },
      radius{ radius_ }
{
   std::cout << "Created Physics object\n";
}
};   // namespace sand
