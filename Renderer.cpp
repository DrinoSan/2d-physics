#include "raylib.h"

#include "PhysicsWorld.h"
#include "Renderer.h"

namespace sand
{
void Renderer_t::render( const PhysicsWorld_t& world )
{
   BeginDrawing();
   ClearBackground( RAYWHITE );   // White background

   for ( const auto& obj : world.getObjects() )
   {
      obj->render();
   }

   DrawLine( 0, world.getGroundY(), screenWidth, world.getGroundY(),
             BLACK );   // Draw ground
   EndDrawing();
}
};   // namespace sand
