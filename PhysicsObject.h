#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include <iostream>

#include "raylib.h"
#include "raymath.h"

namespace sand
{
class PhysicsObject_t
{
 public:
   PhysicsObject_t( Vector2 position_ = { 400 / 2.0f, 50.0f },
                    Vector2 velocity_ = { 0.0f, 0.0f }, float mass_ = 1.0f );

   virtual ~PhysicsObject_t() = default;

   // Function to update objects velocity, acceleration, position based ob
   // prevoius values
   virtual void update( float dt );

   // Check if object hit the ground
   virtual void onGroundCollision( float groundY ) = 0;

   // Get lowest point of object
   virtual float getBottomExtent() const = 0;

   // Function to draw given object
   virtual void render() const = 0;

   Vector2 position;       // Position in 2D space
   Vector2 velocity;       // Velocity in pixels/s
   Vector2 acceleration;   // Acceleration in pixels/s^2
   float   mass;           // Mass (unused here but included for extensibility)
};

};   // namespace sand
#endif   // PHYSICS_OBJECT_H
