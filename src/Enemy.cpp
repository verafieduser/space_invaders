#include "Enemy.h"
// #include "Sprite.h"
#include "Bullet.h"
#include "System.h"
#include <SDL2/SDL_image.h>
// #include <iostream>

namespace space_invaders
{

    Enemy::Enemy(int x, int y, int w, int h, std::string image_path, int randomSeed) : Sprite(x, y, w, h, image_path)
    {
        name = "Enemy";
        sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
        health = 1;
        srand(randomSeed);
        movementPattern = rand() % 3;
        speed = (rand() % 3) + 2;           //could also be affected by difficulty setting
        shootingSpeed = rand() % 200 + 100; //could be affected in a difficuly setting thing available in system?
    }   

    Enemy *Enemy::getInstance(int x, int y, int w, int h, std::string image_path, int randomSeed)
    {
        return new Enemy(x, y, w, h, image_path, randomSeed);
    }

    Enemy::~Enemy()
    {
        SDL_DestroyTexture(sprite);
    }

    Component *Enemy::shoot()
    {
        return Bullet::getInstance((getX() - getW() - speed - 1), (getY() + 40), 100, 20, "laser2.png", 13, false);
    }

    void Enemy::moveLeft()
    {
        int value = -1 * speed;
        setX(value);
    }

    Component *Enemy::perform(std::vector<Component *>& comps)
    {
        collisionConsequences(comps);
        
        if (isKilled())
        {
            name = "Defeated enemy";
        }

        else if (isOutOfBoundsLeft())
        {
            kill();
        }

        moveLeft();
        switch (movementPattern)
        {
        case 0:

            if (movementCounter > 100 && movementCounter <= 200)
            {
                moveUp();
            }
            else if (movementCounter <= 100 || (movementCounter > 200 && movementCounter < 300))
            {
                moveDown();
            }
            else
            {
                movementCounter = 0;
            }
            movementCounter++;
            break;
        case 1:
            if (movementCounter > 100 && movementCounter <= 200)
            {
                moveDown();
            }
            else if (movementCounter <= 100 || (movementCounter > 200 && movementCounter < 300))
            {
                moveUp();
            }
            else
            {
                movementCounter = 0;
            }
            movementCounter++;
            break;
        case 2:
            moveLeft();
            break;
        case 3:
            if (movementCounter < 100)
            {
                moveUp();
                moveUp();
            }
            else if (movementCounter > 100 && movementCounter < 200)
            {
                moveDown();
                moveDown();
            }
            movementCounter++;
            break;
        }

        shootingCooldown -= 1;

        if (shootingCooldown <= 0)
        {
            shootingCooldown = shootingSpeed;
            return shoot();
        }
        return NULL;
    }
}