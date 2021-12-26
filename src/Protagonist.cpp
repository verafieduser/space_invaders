#include "Protagonist.h"
#include "Sprite.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <SDL2/SDL_image.h>

namespace cwing
{

    Protagonist::Protagonist(int x, int y, int w, int h, std::string image_path) : Sprite(x, y, w, h, image_path)
    {
        sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
    }

    Protagonist::~Protagonist()
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(sprite);
    }

    Protagonist *Protagonist::getInstance(int x, int y, int w, int h, std::string image_path)
    {
        return new Protagonist(x, y, w, h, image_path);
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
        //implement this
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
            moveUp();
            break;
        case SDLK_LEFT:
            moveDown();
            break;
        case SDLK_UP:
            moveLeft();
            break;
        case SDLK_DOWN:
            moveRight();
            break;
        }
    }

    // void Protagonist::draw() const
    // {

    //     SDL_RenderCopy(sys.get_ren(), sprite, NULL, &getRect());

    //     SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
    // }
}