#include "Debris.h"
#include "System.h"

namespace space_invaders
{

    Debris::Debris(int x, int y, int w, int h, std::string image_path, int speed, short int hp) : Sprite(x, y, w, h, image_path)
    {
        sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
        speed = speed;
        srand(speed + x + y + w + h);
        spinEveryXFrame = rand() % 3 + 3;
        spinDir = rand() % 2 - 1;
        if (spinDir == 0)
        {
            spinDir = spinDir + 1;
        }
        health = hp;
        name = "Debris";
    }

    Debris *Debris::getInstance(int x, int y, int w, int h, std::string image_path, int speed, short int health)
    {
        return new Debris(x, y, w, h, image_path, speed, health);
    }

    Debris::~Debris()
    {
        SDL_DestroyTexture(sprite);
    }

    void Debris::moveLeft()
    {
        int value = -1 * speed;
        setX(value);
    }

    void Debris::spinDebris(const int &speed)
    {
        if (angle > 360 || angle < -360)
        {
            angle = 0;
        }
        setAngle(angle + (speed * spinDir));
    }

    void Debris::setAngle(const int &newAngle)
    {
        angle = newAngle;
    }

    Component *Debris::perform(std::vector<Component *>& comps)
    {
        collisionConsequences(comps);
        moveLeft();
        spinCounter++;
        if (spinCounter == spinEveryXFrame)
        {
            spinDebris(speed);
            spinCounter = 0;
        }

        if (isKilled())
        {
            name = "Destroyed debris";
        }
        else if (isOutOfBoundsLeft())
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
    }
}