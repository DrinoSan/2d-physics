#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include <iostream>

#include "raylib.h"
#include "raymath.h"

namespace sand
{
enum class ObjectType
{
   Circle,
   Rectangle,
   Triangle,
   Custom,
   None,
};

class PhysicsObject_t
{
 public:
   PhysicsObject_t( Vector2 position_ = { 400 / 2.0f, 50.0f },
                    Vector2 velocity_ = { 0.0f, 0.0f }, float mass_ = 1.0f,
                    ObjectType type_ = ObjectType::None );

   virtual ~PhysicsObject_t() = default;

   // Function to update objects velocity, acceleration, position based ob
   // prevoius values
   virtual void update( float dt, bool isGravityActivated );

   // Check if object hit the ground
   virtual void onGroundCollision( float groundY, bool isGravityActivated ) = 0;
   // Check border collision
   virtual void onBorderCollision( float leftBorderX, float rightBorderX ) = 0;

   // Resolve colision
   virtual void onObjectCollision( PhysicsObject_t& other ) = 0;

   // Get lowest point of object
   virtual float getBottomExtent() const = 0;
   virtual float getLeftExtent() const   = 0;
   virtual float getRightExtent() const  = 0;

   // Function to draw given object
   virtual void render() const = 0;

   // Dump
   // clang-format off
   virtual void dump() const
   {
       std::cout << "==========OBJECT DUMP==========\n";
       std::cout << "Position:     (" << position.x << ", " << position.y << ") pixels\n";
       std::cout << "Velocity:     (" << velocity.x << ", " << velocity.y << ") pixels/s\n";
       std::cout << "Acceleration: (" << acceleration.x << ", " << acceleration.y << ") pixels/s^2\n";
       std::cout << "Mass:         " << mass << " units\n";
       std::cout << "==============================\n";
   }
   // clang-format on

   Vector2    position;       // Position in 2D space
   Vector2    velocity;       // Velocity in pixels/s
   Vector2    acceleration;   // Acceleration in pixels/s^2
   float      mass;           // Mass not used currently but later..
   ObjectType type;
};

};   // namespace sand
#endif   // PHYSICS_OBJECT_H
