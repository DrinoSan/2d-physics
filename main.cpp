#include <iostream>
#include <unistd.h>

#include "CircleObject.h"
#include "GravityForce.h"
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
   InitWindow( screenWidth, screenHeight, "2D Physics - By Sand" );
   SetTargetFPS( 60 );   // Target 60 frames per second

   // Create PhysicsWorld
   sand::PhysicsWorld_t world( screenHeight - 10, true );

   // Create Renderer
   sand::Renderer_t renderer( screenWidth, screenHeight );

   // Create GravityForce with gravity strength (e.g., 980 pixels/s^2)
   std::unique_ptr<sand::Force_t> gravity =
       std::make_unique<sand::GravityForce_t>( 300.0f );

   // Add gravity
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
