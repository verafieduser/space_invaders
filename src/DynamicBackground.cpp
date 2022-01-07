#include "DynamicBackground.h"
#include "System.h"

namespace space_invaders
{

    DynamicBackground *DynamicBackground::getInstance(int x, int y, int w, int h, std::string image_path)
    {
        return new DynamicBackground(x, y, w, h, image_path);
    }

    Component *DynamicBackground::perform(const std::vector<Component *>& comps)
    {
        if (speedCounter == moveEveryXFrame)
        {
            moveLeft();
            // spinImage(speed);
            speedCounter = -1;
        }

        speedCounter++;
        if (isOutOfBoundsLeft())
        {
            kill();
        }
        return NULL;
    }

    void DynamicBackground::spinImage(int &speed)
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

        int value = -1 * speed;
        setX(value);
    }

    DynamicBackground::~DynamicBackground()
    {
        SDL_DestroyTexture(sprite);
    }
    DynamicBackground::DynamicBackground(int x, int y, int w, int h, std::string image_path) : Actor(x, y, w, h, image_path)
    {
        imagepath = image_path;
        name = "DynamicBackground";
        collidable = false;
        speed = 1;
        moveEveryXFrame = 2;
        // srand(speed+x+y+w+h);
        // spinDir = rand() % 2-1;
        // if (spinDir == 0){
        //     spinDir = spinDir+1;
        // }
    }

    void DynamicBackground::draw() const
    {

        if (isOutOfBoundsRight())
        {
            return;
        }
        Actor::draw();

        // SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

        // int success = SDL_RenderCopyEx(sys.get_ren(), sprite, NULL, &getRect(), angle, NULL, flip) + 1;
        // if (!success)
        // {
        //     std::cout << SDL_GetError() << " in RenderCopyEx sprite in dynamicBackground \n" << imagepath << std::endl;
        // }
    }
}