#include "Protagonist.h"
// #include "Sprite.h"
#include "Bullet.h"
//#include "Controller.h"

namespace space_invaders
{
    Protagonist::Protagonist(int x, int y, int w, int h, std::string image_path, Controller &controller, Healthbar &healthbar) : Sprite(x, y, w, h, image_path), healthbar(healthbar), controller(controller)
    {
        speed = 10;
        health = 3;
        name = "Protagonist";
    }

    Protagonist *Protagonist::getInstance(int x, int y, int w, int h, std::string image_path, Controller &controller, Healthbar &healthbar)
    {
        return new Protagonist(x, y, w, h, image_path, controller, healthbar);
    }

    Protagonist::~Protagonist()
    {
        healthbar.kill();
        SDL_DestroyTexture(sprite);
    }

    void Protagonist::takeDamage()
    {
        if (damageCooldown == 0)
        {
            healthbar.updateHealth(-1);
            health--;
            damageCooldown = 60;
        } 
        if(health <= 0){
            kill();
        }
        //damageCooldown = 60;
    };

    Component *Protagonist::shoot()
    {
        return Bullet::getInstance((getX() + getW() + speed + 1), (getY() + 45), 30, 10, "laser.png", 30, true);
    }

    Component *Protagonist::perform(std::vector<Component *>& comps)
    {
        collisionConsequences(comps);
        // if (health <= 0)
        // {
        //     kill();
        //     //TODO: return explosion here?
        // }

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