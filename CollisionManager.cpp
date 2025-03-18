#include "CollisionManager.h"

namespace sand
{
// ----------------------------------------------------------------------------
void CollisionManager_t::checkCollisions(
    const std::vector<std::unique_ptr<PhysicsObject_t>>& objects,
    float                                                groundY )
{
   for ( auto& obj : objects )
   {
      if ( obj->getBottomExtent() > groundY && obj->velocity.y > 0 )
      {
         // Should be called for each object
         obj->onGroundCollision( groundY );

         // TODO: Add collision handling for each object pair
         for ( size_t i = 0; i < objects.size(); ++i )
         {
            for ( size_t j = i + 1; i < objects.size() - 1; ++j )
            {
               // TODO: Implement me
               // if( ! checkCollision( *objects[i], *objects[j] ) )
               //{
               //   continue;
               //}

               // objects[i]->onObjectCollision( *objects[j],.... );
               // objects[j]->onObjectCollision( *objects[i],.... );
            }
         }
      }
   }
}

// ----------------------------------------------------------------------------
bool CollisionManager_t::checkCollision( const PhysicsObject_t& obj1,
                                         const PhysicsObject_t& obj2 )
{
   switch ( obj1.type )
   {
   case ObjectType::Circle:
   {
      switch ( obj2.type )
      {
      case ObjectType::Circle:
      {
         return checkCircleCircle( obj1, obj2 );
      }
      case ObjectType::Rectangle:
      {
         return checkCircleRectangle( obj1, obj2 );
      }
      }
      break;
   }
   case ObjectType::Rectangle:
   {
      break;
   }
   default:
   {
      // This does not exist in my world
      return false;
   }
   };

   return false;
}

// ----------------------------------------------------------------------------
bool CollisionManager_t::checkCircleCircle( const PhysicsObject_t& obj1,
                                            const PhysicsObject_t& obj2 )
{
   return false;
}

// ----------------------------------------------------------------------------
bool CollisionManager_t::checkCircleRectangle( const PhysicsObject_t& obj1,
                                               const PhysicsObject_t& obj2 )
{
   return false;
}
};   // namespace sand
