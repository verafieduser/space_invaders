#ifndef COLLISION_H
#define COLLISION_H

#include <string>
#include <SDL2/SDL.h>
#include "Component.h"

namespace space_invaders
{
    class Collision
    {
    public:
        static bool AABB(const SDL_Rect &rectA, const SDL_Rect &rectB);
        static const bool canCollideWith(const Component *c, Component *c2);
    };
}

#endif