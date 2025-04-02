#ifndef RENDERER_H
#define RENDERER_H

namespace sand
{
class PhysicsWorld_t;

class Renderer_t
{
 public:
   Renderer_t( int w, int h ) : screenWidth{ w }, screenHeight{ h } {}
   void render( PhysicsWorld_t& world );

 private:
   int screenWidth;
   int screenHeight;
};

};

#endif
