#include "Protagonist.h"
#include "Sprite.h"
#include "Bullet.h"
#include "System.h"
#include <SDL2/SDL_image.h>
#include <iostream>

namespace cwing
{

    Protagonist::Protagonist(int x, int y, int w, int h, std::string image_path) : Sprite(x, y, w, h, image_path)
    {
        sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
    }

    Protagonist::~Protagonist()
    {
        SDL_DestroyTexture(sprite);
    }

    Protagonist *Protagonist::getInstance(int x, int y, int w, int h, std::string image_path)
    {
        return new Protagonist(x, y, w, h, image_path);
    }

    Component* Protagonist::shoot(){
        return Bullet::getInstance((getX() + 90), (getY() + 45), 45, 8, "laser.png", 30, true);
    }

    Component* Protagonist::perform(SDL_Event event)
    {
        shootingCooldown -= 1;

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT]){
            moveRight();
            moveDown();
        } else if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT]){
            moveDown();
            moveLeft();
        } else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]){
            moveUp();
            moveLeft();
        } else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]){
            moveUp();
            moveRight();
        } else if(state[SDL_SCANCODE_DOWN]){
           moveDown();
        } else if (state[SDL_SCANCODE_UP]){
            moveUp();
        } else if (state[SDL_SCANCODE_LEFT]){
            moveLeft();
        } else if (state[SDL_SCANCODE_RIGHT]){
            moveRight();
        } 
        
        if (state[SDL_SCANCODE_SPACE] && shootingCooldown <= 0){
            shootingCooldown = 10;
            return shoot();
        }
        return NULL;
    }
}