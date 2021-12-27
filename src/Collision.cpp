
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include "Collision.h"
#include <SDL2/SDL_image.h>

namespace cwing
{
    bool Collision::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB)
    {
        if (rectA.x + rectA.w >= rectB.x &&
            rectB.x + rectB.w >= rectA.x &&
            rectA.y + rectA.h >= rectB.y &&
            rectB.y + rectB.h >= rectA.y)
        {
            return true;
        }
        return false;
    }

}