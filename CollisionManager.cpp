#include "CollisionManager.h"
#include "CircleObject.h"

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
         }
      }

      for( auto& obj : objects )
      {
            // TODO: Add collision handling for each object pair
            for ( size_t i = 0; i < objects.size(); ++i )
            {
               for ( size_t j = i + 1; j < objects.size(); ++j )
               {
                  if ( !checkCollision( *objects[ i ], *objects[ j ] ) )
                  {
                     continue;
                  }

                  objects[i]->onObjectCollision( *objects[j] );
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
   const CircleObject_t* c1 = dynamic_cast<const CircleObject_t*>( &obj1 );
   const CircleObject_t* c2 = dynamic_cast<const CircleObject_t*>( &obj2 );

   // Distance between Center A and Center B
   auto d = Vector2Distance( c1->position, c2->position );

   return d <= c1->radius + c2->radius;
}

// ----------------------------------------------------------------------------
bool CollisionManager_t::checkCircleRectangle( const PhysicsObject_t& obj1,
                                               const PhysicsObject_t& obj2 )
{
   return false;
}
};   // namespace sand
