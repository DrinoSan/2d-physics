#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "CircleObject.h"
#include "PhysicsWorld.h"
#include "Renderer.h"

namespace sand
{
// Menue
bool gravityEnabled   = true;
int  shapeSelected    = 0;
char radiusText[ 32 ] = "10.0";
char widthText[ 32 ]  = "1.0";
char heightText[ 32 ] = "1.0";
bool dropdownEditMode = false;
bool radiusEditMode   = false;
bool widthEditMode    = false;
bool heightEditMode   = false;

void Renderer_t::render( PhysicsWorld_t& world )
{
   BeginDrawing();
   ClearBackground( RAYWHITE );   // White background

   // GuiCheckBox((Rectangle){ 565, 80, 20, 20 }, "SHOW CONTENT AREA",
   // &showContentArea);
   GuiCheckBox( ( Rectangle ){ 20, 20, 20, 20 }, "Gravity", &gravityEnabled );

   if ( GuiDropdownBox( ( Rectangle ){ 20, 50, 150, 20 }, "Circle;Rectangle",
                        &shapeSelected, dropdownEditMode ) )
   {
      dropdownEditMode = !dropdownEditMode;
   }

   if ( shapeSelected == 0 )
   {
      GuiLabel( ( Rectangle ){ 20, 80, 50, 20 }, "Radius:" );
      if ( GuiTextBox( ( Rectangle ){ 80, 80, 100, 20 }, radiusText, 32,
                       radiusEditMode ) )
      {
         radiusEditMode = !radiusEditMode;
      }
   }
   else if ( shapeSelected == 1 )
   {
      GuiLabel( ( Rectangle ){ 20, 80, 50, 20 }, "Width:" );
      if ( GuiTextBox( ( Rectangle ){ 80, 80, 100, 20 }, widthText, 32,
                       widthEditMode ) )
      {
         widthEditMode = !widthEditMode;
      }

      GuiLabel( ( Rectangle ){ 20, 110, 50, 20 }, "Height:" );
      if ( GuiTextBox( ( Rectangle ){ 80, 110, 100, 20 }, heightText, 32,
                       heightEditMode ) )
      {
         heightEditMode = !heightEditMode;
      }
   }

   if ( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) )
   {
      // Create the circle PhysicsObject
      float radius = std::stof( radiusText );
      float mass   = radius / 10.0f;

      std::unique_ptr<sand::PhysicsObject_t> circle =
          std::make_unique<sand::CircleObject_t>( radius );
      circle->position = GetMousePosition();
      circle->mass     = mass;

      // Add circle to PhysicsWorld
      world.addObject( std::move( circle ) );
   }

   for ( const auto& obj : world.getObjects() )
   {
      obj->render();
   }

   DrawLine( 0, world.groundY, screenWidth, world.groundY,
             BLACK );   // Draw ground

   if ( world.hasSideBorder )
   {
      DrawLine( ( GetScreenWidth() / 2 ) - world.distanceFromCenter + 10, 0,
                ( GetScreenWidth() / 2 ) - world.distanceFromCenter + 10,
                world.groundY,
                BLACK );   // Draw leftBorder

      DrawLine( ( GetScreenWidth() / 2 ) + world.distanceFromCenter - 10, 0,
                ( GetScreenWidth() / 2 ) + world.distanceFromCenter - 10,
                world.groundY,
                BLACK );   // Draw rightBorder
   }

   world.isGravityActivated = gravityEnabled;

   EndDrawing();
}
};   // namespace sand
