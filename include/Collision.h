#include <string>
#include <SDL2/SDL.h>
#include "Component.h"

namespace cwing
{
    class Collision
    {
    public:
        static bool AABB(const SDL_Rect &rectA, const SDL_Rect &rectB);
        static bool canCollide(Component *c, Component *c2);
    };
}