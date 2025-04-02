#ifndef CIRCLE_OBJECT_H
#define CIRCLE_OBJECT_H

#include "PhysicsObject.h"

namespace sand
{
class CircleObject_t : public PhysicsObject_t
{
 public:
   CircleObject_t( float      radius_ = 20.0f,
                   ObjectType type_   = ObjectType::Circle )
       : radius{ radius_ }
   {
      type = type_;
   }

   ~CircleObject_t() override = default;

   void update( float dt, bool isGravityActivated ) override;

   void onGroundCollision( float groundY, bool isGravityActivated ) override;
   void onBorderCollision( float leftBorderX, float rightBorderX ) override;

   float getBottomExtent() const override { return position.y + radius; }
   float getLeftExtent() const override { return position.x - radius; }
   float getRightExtent() const override { return position.x + radius; }

   void onObjectCollision( PhysicsObject_t& other ) override;

   // clang-format off
   void dump() const override
   {
       // Call parent class dump first
       PhysicsObject_t::dump();

       // Add child class specific members
       std::cout << "==========SPACESHIP DETAILS==========\n";
       std::cout << "Radius:         " << radius << " units\n";
       std::cout << "=====================================\n";
   }
   // clang-format on

   void render() const override { DrawCircleV( position, radius, RED ); }

   float radius;   // Radius for rendering and collision
};

};   // namespace sand
#endif
