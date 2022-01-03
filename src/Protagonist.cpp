#include "Protagonist.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Controller.h"
#include "System.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

namespace cwing
{
    Protagonist::Protagonist(int x, int y, int w, int h, std::string image_path, Controller &controller) : Sprite(x, y, w, h, image_path), controller(controller)
    {
        sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
        SPEED = 10;
        health = 3;
        name = "Protagonist";
    }

    Protagonist *Protagonist::getInstance(int x, int y, int w, int h, std::string image_path, Controller &controller)
    {
        return new Protagonist(x, y, w, h, image_path, controller);
    }

    Protagonist::~Protagonist()
    {
        healthbar->~Healthbar();
        SDL_DestroyTexture(sprite);
    }

    void Protagonist::setHealthbar(Healthbar *h)
    {
        healthbar = h;
    }

    // void Protagonist::setController(Controller &c)
    // {
    //     controller = c;
    // }

    Component *Protagonist::shoot()
    {
        return Bullet::getInstance((getX() + getW() + SPEED + 1), (getY() + 45), 30, 10, "laser.png", 30, true);
    }

    Component *Protagonist::perform(SDL_Event event)
    {
        if (health <= 0)
        {
            kill();
            //TODO: return explosion here?
        }

        if (damageCooldown > 0)
        {
            damageCooldown--;
        }

        shootingCooldown -= 1;

        const Uint8 *state = controller.getKeyboardState();

        if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT])
        {
            moveRight();
            moveDown();
        }
        else if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT])
        {
            moveDown();
            moveLeft();
        }
        else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT])
        {
            moveUp();
            moveLeft();
        }
        else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT])
        {
            moveUp();
            moveRight();
        }
        else if (state[SDL_SCANCODE_DOWN])
        {
            moveDown();
        }
        else if (state[SDL_SCANCODE_UP])
        {
            moveUp();
        }
        else if (state[SDL_SCANCODE_LEFT])
        {
            moveLeft();
        }
        else if (state[SDL_SCANCODE_RIGHT])
        {
            moveRight();
        }

        if (state[SDL_SCANCODE_SPACE] && shootingCooldown <= 0)
        {
            shootingCooldown = 10;
            return shoot();
        }
        return NULL;
    }
}