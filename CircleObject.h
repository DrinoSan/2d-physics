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

   void  update( float dt ) override;
   void  onGroundCollision( float groundY ) override;
   float getBottomExtent() const override { return position.y + radius; }
   void  onObjectCollision( PhysicsObject_t& other ) override;

   void render() const override { DrawCircleV( position, radius, RED ); }

   float radius;   // Radius for rendering and collision
};

};   // namespace sand
#endif
