#include "Bullet.h"

namespace space_invaders
{
    Bullet::Bullet(int x, int y, int w, int h, std::string image_path, int s, bool isFromProtagonist) : Actor(x, y, w, h, image_path)
    {
        if(isFromProtagonist){
            name = "Protagonist Bullet";
        } else {
            name = "Enemy Bullet";
        }
        health = 1;
        speed = s;

        if (isFromProtagonist)
        {
            dir = RIGHT;
        }
        else
        {
            dir = LEFT;
        }
    }

    Bullet *Bullet::getInstance(int x, int y, int w, int h, std::string image_path, int speed, bool isFromProtagonist)
    {
        return new Bullet(x, y, w, h, image_path, speed, isFromProtagonist);
    }

    Bullet::~Bullet()
    {
        SDL_DestroyTexture(sprite);
    }

    void Bullet::moveRight()
    {
        setX(speed);
    }

    void Bullet::moveLeft()
    {
        int value = -1 * speed;
        setX(value);
    }

    Component *Bullet::perform(const std::vector<Component *> &comps)
    {
        if (dir == RIGHT)
        {
            moveRight();
            if (isOutOfBoundsRight())
            {
                kill();
            }
        }
        else
        {
            moveLeft();
            if (isOutOfBoundsLeft())
            {
                kill();
            }
        }
        collisionConsequences(comps);

        return NULL;
    }

}