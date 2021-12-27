#include "Debris.h"
#include "Sprite.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <SDL2/SDL_image.h>
#include <iostream>

namespace cwing
{

    Debris::Debris(int x, int y, int w, int h, std::string image_path, int speed) : Sprite(x, y, w, h, image_path)
    {
        sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
        SPEED = speed;
    }

    Debris::~Debris()
    {
        SDL_DestroyTexture(sprite);
    }

    Debris *Debris::getInstance(int x, int y, int w, int h, std::string image_path, int speed)
    {
        return new Debris(x, y, w, h, image_path, speed);
    }

    void Debris::moveLeft()
    {
        int value = -1 * SPEED;
        setX(value);
    }

    void Debris::spinDebris(const int &speed)
    {
        //TODO: randomize spin direction!
        if (angle > 360 || angle < -360)
        {
            angle = 0;
        }
        setAngle(angle + speed);
    }

    void Debris::setAngle(const int &newAngle)
    {
        angle = newAngle;
    }

    Component *Debris::perform(SDL_Event event)
    {

        moveLeft();
        spinDebris(SPEED);

        if (isOutOfBoundsLeft())
        {
            kill();
        }

        return NULL;
    }

    void Debris::draw() const
    {
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

        int success = SDL_RenderCopyEx(sys.get_ren(), sprite, NULL, &getRect(), angle, NULL, flip) + 1;
        if (!success)
        {
            std::cout << SDL_GetError() << " in RenderCopyEx sprite in Debris \n";
        }

        // success = SDL_RenderCopyEx(sys.get_ren(), texture, NULL, &getRect(), angle, NULL, flip) +1;
        // if(!success){
        //     std::cout << SDL_GetError() << " in RenderCopyEx texture in Debris \n" << "";
        // }
    }
}