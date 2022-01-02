#include "DynamicBackground.h"
#include <iostream>

namespace cwing
{

    DynamicBackground *DynamicBackground::getInstance(int x, int y, int w, int h, std::string image_path)
    {
        return new DynamicBackground(x, y, w, h, image_path);
    }

    Component *DynamicBackground::perform(SDL_Event event)
    {
        if (speedCounter == moveEveryXFrame)
        {
            moveLeft();
            spinImage(SPEED);
            speedCounter = -1;
        }

        speedCounter++;
        if (isOutOfBoundsLeft())
        {
            int newLocation = SCREEN_WIDTH + 5000;
            setX(newLocation);
        }
        return NULL;
    }

    void DynamicBackground::spinImage(int speed)
    {
        if (angle > 360 || angle < -360)
        {
            angle = 0;
        }
        setAngle(angle + (speed * spinDir));
    }

    void DynamicBackground::setAngle(const int &newAngle)
    {
        angle = newAngle;
    }

    void DynamicBackground::moveLeft()
    {

        int value = -1 * SPEED;
        setX(value);
    }

    DynamicBackground::~DynamicBackground()
    {
        SDL_DestroyTexture(sprite);
    }
    DynamicBackground::DynamicBackground(int x, int y, int w, int h, std::string image_path) : Sprite(x, y, w, h, image_path)
    {
        name = "DynamicBackground";
        collidable = false;
        SPEED = 1;
        moveEveryXFrame = 2;
    }

    void DynamicBackground::draw() const
    {
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

        int success = SDL_RenderCopyEx(sys.get_ren(), sprite, NULL, &getRect(), angle, NULL, flip) + 1;
        if (!success)
        {
            std::cout << SDL_GetError() << " in RenderCopyEx sprite in dynamicBackground \n";
        }
    }
}