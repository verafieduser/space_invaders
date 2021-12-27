#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Bullet.h"
#include "Sprite.h"
#include "Session.h"
#include "System.h"
#include "Collision.h"

namespace cwing
{

    Bullet::Bullet(int x, int y, int w, int h, std::string image_path, int speed, bool isFromProtagonist) : Sprite(x, y, w, h, image_path)
    {
        sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
        SPEED = speed;
        health = 1;
        if (isFromProtagonist)
        {
            dir = RIGHT;
        }
        else
        {
            dir = LEFT;
        }
    }

    Bullet::~Bullet()
    {
        SDL_DestroyTexture(sprite);
    }

    Bullet *Bullet::getInstance(int x, int y, int w, int h, std::string image_path, int speed, bool isFromProtagonist)
    {
        return new Bullet(x, y, w, h, image_path, speed, isFromProtagonist);
    }

    void Bullet::moveRight()
    {
        setX(SPEED);
    }

    void Bullet::moveLeft()
    {
        int value = -1 * SPEED;
        setX(value);
    }

    Component *Bullet::perform(SDL_Event event)
    {
        if (dir == RIGHT)
        {
            moveRight();
            if (isOutOfBoundsRight() || health <= 0)
            {
                kill();
            }
        }
        else
        {
            moveLeft();
            if (isOutOfBoundsLeft() || health <= 0)
            {
                kill();
            }
        }

        return NULL;
    }

}

// namespace cwing
// {
//     Bullet::Bullet(int x, int y, int w, int h, std::string image_path, int speed) : Sprite(x, y, w, h, image_path)
//     {
//         sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
//         SPEED = speed;
//     }

//     Bullet *Bullet::getInstance(int x, int y, int w, int h, std::string images_path, int speed)
//     {
//         return new Bullet(x);
//     }

//     Bullet::~Bullet()
//     {
//         SDL_DestroyTexture(texture);
//     }

//     void Bullet::draw() const
//     {
//         const SDL_Rect &rect = getRect();
//         //SDL_RenderCopy(sys.ren, texture, NULL, &getRect());
//         SDL_RenderCopy(sys.get_ren(), texture, NULL, &rect);
//     }

//     void Bullet::perform(SDL_Event event)
//     {
//         moveRight();
//     }
// }