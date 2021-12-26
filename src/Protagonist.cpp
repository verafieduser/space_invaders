#include "Protagonist.h"
#include "Sprite.h"
#include "Bullet.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <SDL2/SDL_image.h>
#include <iostream>

namespace cwing
{

    Protagonist::Protagonist(int x, int y, int w, int h, std::string image_path, Session &session) : Sprite(x, y, w, h, image_path, session)
    {
        sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
    }

    Protagonist::~Protagonist()
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(sprite);
    }

    Protagonist *Protagonist::getInstance(int x, int y, int w, int h, std::string image_path, Session &session)
    {
        return new Protagonist(x, y, w, h, image_path, session);
    }
    // void Protagonist::moveUp()
    // {
    //     setX(SPEED);
    // }

    // void Protagonist::moveDown()
    // {
    //     int value = -1 * SPEED;
    //     setX(value);
    // }

    // void Protagonist::moveLeft()
    // {
    //     int value = -1 * SPEED;
    //     setY(value);
    // }

    // void Protagonist::moveRight()
    // {
    //     setY(SPEED);
    // }

    void Protagonist::perform(SDL_Event event)
    {
        // Bullet *bullet = Bullet::getInstance(getX(), getY(), 100, 100, "laser.jpg", session, 30);
        // session.add(bullet);
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                keystates.right = true;
                updateMovement(RIGHT);
                break;
            case SDLK_LEFT:
                keystates.left = true;
                updateMovement(LEFT);
                break;
            case SDLK_UP:
                keystates.up = true;
                updateMovement(UP);
                break;
            case SDLK_DOWN:
                keystates.down = true;
                updateMovement(DOWN);
                break;
            case SDLK_SPACE:
                Bullet *bullet = Bullet::getInstance(getX(), getY(), 100, 100, "laser.jpg", session, 30);
                session.add(bullet);
                break;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                keystates.right = false;
                break;
            case SDLK_LEFT:
                keystates.left = false;
                break;
            case SDLK_UP:
                keystates.up = false;
                break;
            case SDLK_DOWN:
                keystates.down = false;
                break;
            }
        }
    }

    // void Protagonist::draw() const
    // {

    //     SDL_RenderCopy(sys.get_ren(), sprite, NULL, &getRect());

    //     SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
    // }
}