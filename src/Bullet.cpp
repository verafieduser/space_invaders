#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Bullet.h"
#include "Sprite.h"
#include "System.h"

namespace cwing
{

    Bullet::Bullet(int x, int y, int w, int h, std::string image_path, Session &session, int speed) : Sprite(x, y, w, h, image_path, session)
    {
        sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
        SPEED = speed;
    }

    Bullet::~Bullet()
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(sprite);
    }

    Bullet *Bullet::getInstance(int x, int y, int w, int h, std::string image_path, Session &session, int speed)
    {
        return new Bullet(x, y, w, h, image_path, session, speed);
    }

    Component* Bullet::perform(SDL_Event event)
    {
        moveRight();
        return NULL;
    }

    // void Bullet::draw() const
    // {
    //     // SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

    //     // SDL_RenderCopyEx(sys.get_ren(), sprite, NULL, &getRect(), angle, NULL, flip);

    //     SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect(), angle, NULL, flip);
    // }
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