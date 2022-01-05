#include "System.h"
#include "Collision.h"
#include "Bullet.h"
#include <iostream>

namespace space_invaders
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

    const bool Collision::canCollideWith(const Component *c, Component *c2) {

        std::string name1 = c->getName();
        std::string name2 = c2->getName();

        if(!c->isCollidable() || !c2->isCollidable()){
            return false;
        }

        if (name1 == "Protagonist" && name2 == "Bullet")
        {
            Bullet* bullet = dynamic_cast<Bullet *> (c2);
            if (!bullet->fromProtagonist() && Collision::AABB(c2->getRect(), c->getRect()))
            {
                return true;
            }
        }

        else if (name2 == "Bullet" && name1 == "Enemy" )
        {
            Bullet* bullet = dynamic_cast<Bullet *> (c2);
            if (bullet->fromProtagonist() && Collision::AABB(c2->getRect(), c->getRect()))
            {
                return true;
            }
        }

        else if (name2 == "Bullet" && name1 == "Debris")
        {
            if (Collision::AABB(c2->getRect(), c->getRect()))
            {

                return true;
            }
        }

        // if (name1 == "Bullet" && name2 == "Debris")
        // {
        //     if (Collision::AABB(c2->getRect(), c->getRect()))
        //     {

        //         return true;
        //     }
        // }
		
        else if (name1 == "Protagonist" && name2 == "Debris")
        {
            if (Collision::AABB(c->getRect(), c2->getRect()))
            {

                return true;
            }
        }

        else if (name1 == "Protagonist" && name2 == "Enemy")
        {
            if (Collision::AABB(c2->getRect(), c->getRect()))
            {

                return true;
            }
        }

        else if (name1 == "Bullet" && name2 == "Bullet")
        {
            if (Collision::AABB(c2->getRect(), c->getRect()))
            {

                return true;
            }
        }

        return false;
    }
}