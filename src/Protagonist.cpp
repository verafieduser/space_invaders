#include "Protagonist.h"
#include "Sprite.h"
#include "Bullet.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <SDL2/SDL_image.h>
#include <iostream>

namespace cwing
{

    Protagonist::Protagonist(int x, int y, int w, int h, std::string image_path, Session &session) : Sprite(x, y, w, h, image_path, session)
    {
        sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
    }

    Protagonist::~Protagonist()
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(sprite);
    }

    Protagonist *Protagonist::getInstance(int x, int y, int w, int h, std::string image_path, Session &session)
    {
        return new Protagonist(x, y, w, h, image_path, session);
    }
    // void Protagonist::moveUp()
    // {
    //     setX(SPEED);
    // }

    // void Protagonist::moveDown()
    // {
    //     int value = -1 * SPEED;
    //     setX(value);
    // }

    // void Protagonist::moveLeft()
    // {
    //     int value = -1 * SPEED;
    //     setY(value);
    // }

    // void Protagonist::moveRight()
    // {
    //     setY(SPEED);
    // }


    // void Protagonist::updateMovement(Direction dir)
    // {
    //     switch (dir)
    //     {
    //     case UP:
    //         moveUp();
    //         if (keystates.left)
    //         {
    //             moveLeft();
    //         }
    //         else if (keystates.right)
    //         {
    //             moveRight();
    //         }
    //     case DOWN:
    //         moveDown();
    //         if (keystates.left)
    //         {
    //             moveLeft();
    //         }
    //         else if (keystates.right)
    //         {
    //             moveRight();
    //         }
    //     case LEFT:
    //         moveLeft();
    //         if (keystates.up)
    //         {
    //             moveUp();
    //         }
    //         else if (keystates.down)
    //         {
    //             moveDown();
    //         }
    //     case RIGHT:
    //         moveRight();
    //         if (keystates.up)
    //         {
    //             moveUp();
    //         }
    //         else if (keystates.down)
    //         {
    //             moveDown();
    //         }
    //     }
    // }

    Component* Protagonist::shoot(){
        return Bullet::getInstance(getX(), getY(), 100, 100, "laser.png", session, 30);

    }

    Component* Protagonist::perform(SDL_Event event)
    {


        const Uint8 *state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_SPACE]){
            return shoot();
        }

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
        
        return NULL;


        // Bullet *bullet = Bullet::getInstance(getX(), getY(), 100, 100, "laser.jpg", session, 30);
        // session.add(bullet);
        // if (event.type == SDL_KEYDOWN)
        // {
        //     Direction dir;

        //     switch (event.key.keysym.sym)
        //     {
        //     case SDLK_RIGHT:
        //         dir = RIGHT;
        //         keystates.right = true;
        //         break;
        //     case SDLK_LEFT:
        //         dir = LEFT;
        //         keystates.left = true;
        //         break;
        //     case SDLK_UP:
        //         dir = UP;
        //         keystates.up = true;
        //         break;
        //     case SDLK_DOWN:
        //         dir = DOWN;
        //         keystates.down = true;
        //         break;              
        //             //case SDLK_SPACE:
        //         //    Bullet *bullet = Bullet::getInstance(getX(), getY(), 100, 100, "laser.jpg", session, 30);
        //         //    session.add(bullet);
        //         //    break;
        //     }
        //     updateMovement(dir);
        // }
        // else if (event.type == SDL_KEYUP)
        // {
        //     switch (event.key.keysym.sym)
        //     {
        //     case SDLK_RIGHT:
        //         keystates.right = false;
        //         break;
        //     case SDLK_LEFT:
        //         keystates.left = false;
        //         break;
        //     case SDLK_UP:
        //         keystates.up = false;
        //         break;
        //     case SDLK_DOWN:
        //         keystates.down = false;
        //         break;
        //     }
        //     keystates.up = false;
        //     keystates.down = false;
        //     keystates.right = false;
        //     keystates.left = false;
        // }
    }

    // void Protagonist::draw() const
    // {

    //     SDL_RenderCopy(sys.get_ren(), sprite, NULL, &getRect());

    //     SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
    // }
}