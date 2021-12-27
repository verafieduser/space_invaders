#include <string>
#include <SDL2/SDL.h>

namespace cwing
{
    class Collision
    {
    public:
        static bool AABB(const SDL_Rect &rectA, const SDL_Rect &rectB);
    };
}