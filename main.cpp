#include <iostream>

#include "GravityForce.h"
#include "CircleObject.h"
#include "PhysicsWorld.h"
#include "Renderer.h"
#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main( void )
{
   // Initialization
   //---------------------------------------------------------
   const int screenWidth  = 800;
   const int screenHeight = 450;

   // Initialize Raylib window
   InitWindow( screenWidth, screenHeight, "2D Physics - Falling Circle" );
   SetTargetFPS( 60 );   // Target 60 frames per second

   // Create PhysicsWorld with ground at screenHeight
   sand::PhysicsWorld_t world( screenHeight - 10 );

   // Create Renderer with screen dimensions
   sand::Renderer_t renderer( screenWidth, screenHeight );

   // Create the circle PhysicsObject
   std::unique_ptr<sand::PhysicsObject_t> circle =
       std::make_unique<sand::CircleObject_t>( 20.0f );
   circle->position = { screenWidth / 2.0f,
                        50.0f };   // Start at center horizontally, near top

   std::unique_ptr<sand::PhysicsObject_t> circle2 =
       std::make_unique<sand::CircleObject_t>( 10.0f );
   circle2->position = { (screenWidth / 2.0f), 50.0f };   // Start at center horizontally, near top

   // Add circle to PhysicsWorld
   world.addObject( std::move( circle ) );
   world.addObject( std::move( circle2 ) );

   // Create GravityForce with gravity strength (e.g., 980 pixels/s^2)
   std::unique_ptr<sand::Force_t> gravity =
       std::make_unique<sand::GravityForce_t>(
           980.0f );   // Assuming GravityForce constructor takes a float

   // Add gravity to PhysicsWorld
   world.addForce( std::move( gravity ) );

   // Main game loop
   while ( !WindowShouldClose() )
   {
      // Get time since last frame
      float dt = GetFrameTime();

      // Update physics simulation
      world.update( dt );

      // Render the scene
      renderer.render( world );
   }

   // Cleanup
   CloseWindow();

   return 0;
}
