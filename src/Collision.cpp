#include <SDL2/SDL_ttf.h>
#include "System.h"
#include "Collision.h"
#include <SDL2/SDL_image.h>
#include "Bullet.h"
#include "Protagonist.h"
#include "Enemy.h"
#include "Debris.h"
#include <iostream>
#include <string>

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

    bool Collision::canCollide(Component *c, Component *c2)
    {
        std::string name1 = c->getName();
        std::string name2 = c2->getName();

        if (name1 == "Protagonist" && name2 == "Bullet")
        {
            // std::cout << "Non-prot bullet collided with prot" << std::endl;
            Bullet *b = dynamic_cast<Bullet *>(c2);
            if (!b->isFromProtagonist() && Collision::AABB(c->getRect(), c2->getRect()))
            {
                return true;
            }
        }

        if (name1 == "Bullet" && name2 == "Enemy")
        {
            // std::cout << "Prot-bullet collided with enemy!" << std::endl;
            Bullet *b = dynamic_cast<Bullet *>(c);
            if (b->isFromProtagonist() && Collision::AABB(c->getRect(), c2->getRect()))
            {
                
                return true;
            }
        }

        if (name1 == "Bullet" && name2 == "Debris")
        {
            // std::cout << "Prot-bullet collided with debris" << std::endl;
            if (Collision::AABB(c->getRect(), c2->getRect()))
            {

                return true;
            }
        }

        if (name1 == "Protagonist" && name2 == "Debris")
        {
            // std::cout << "Protagonist collides with Debris!" << std::endl;
            if (Collision::AABB(c->getRect(), c2->getRect()))
            {
                
                return true;
            }
        }

        if (name1 == "Protagonist" && name2 == "Enemy")
        { 
            // std::cout << "Protagonist collides with Enemy!" << std::endl;
            if (Collision::AABB(c->getRect(), c2->getRect()))
            {
               
                return true;
            }
        }

        if (name1 == "Bullet" && name2 == "Bullet")
        { 
            // std::cout << "Bullet collides with Enemy!" << std::endl;
            if (Collision::AABB(c->getRect(), c2->getRect()))
            {
               
                return true;
            }
        }

        return false;
    }


}