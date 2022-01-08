#include "DynamicBackground.h"
#include "System.h"

namespace space_invaders
{
    DynamicBackground::DynamicBackground(int x, int y, int w, int h, std::string image_path) : Actor(x, y, w, h, image_path)
    {
        imagepath = image_path;
        name = "DynamicBackground";
        collidable = false;
        speed = 1;
        moveEveryXFrame = 2;
    }

    DynamicBackground *DynamicBackground::getInstance(int x, int y, int w, int h, std::string image_path)
    {
        return new DynamicBackground(x, y, w, h, image_path);
    }

    DynamicBackground::~DynamicBackground()
    {
        SDL_DestroyTexture(sprite);
    }

    Component *DynamicBackground::perform(const std::vector<Component *> &comps)
    {
        if (speedCounter == moveEveryXFrame)
        {
            moveLeft();
            speedCounter = -1;
        }

        speedCounter++;
        if (isOutOfBoundsLeft())
        {
            kill();
        }
        return NULL;
    }

    void DynamicBackground::draw() const
    {

        if (isOutOfBoundsRight())
        {
            return;
        }
        Actor::draw();
    }

    void DynamicBackground::moveLeft()
    {

        int value = -1 * speed;
        setX(value);
    }
}