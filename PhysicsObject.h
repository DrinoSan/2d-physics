#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "raylib.h"
#include "raymath.h"

namespace sand
{

// TODO: create child classes for objects
class PhysicsObject_t
{
 public:
   PhysicsObject_t( Vector2 position_ = { 400 / 2.0f, 50.0f },
                    Vector2 velocity_ = { 0.0f, 0.0f }, float mass_ = 1.0f,
                    float radius_ = 20.0f );

   Vector2 position;       // Position in 2D space
   Vector2 velocity;       // Velocity in pixels/s
   Vector2 acceleration;   // Acceleration in pixels/s^2
   float   mass;           // Mass (unused here but included for extensibility)
   float   radius;         // Radius for rendering and collision
};

};   // namespace sand
#endif   // PHYSICS_OBJECT_H
