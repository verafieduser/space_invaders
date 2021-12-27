#include "Enemy.h"
#include "Sprite.h"
#include "Bullet.h"
#include "System.h"
#include <SDL2/SDL_image.h>
#include <iostream>

namespace cwing
{

    Enemy::Enemy(int x, int y, int w, int h, std::string image_path) : Sprite(x, y, w, h, image_path)
    {
        sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
        srand(time(NULL));
        movementPattern = rand() % 3;
        SPEED = rand() %5+5;//could also be affected by difficulty setting
        shootingSpeed = rand() %200+100; //could be affected in a difficuly setting thing available in system?
    }

    Enemy::~Enemy()
    {
        SDL_DestroyTexture(sprite);
    }

    Enemy *Enemy::getInstance(int x, int y, int w, int h, std::string image_path)
    {
        return new Enemy(x, y, w, h, image_path);
    }

    Component* Enemy::shoot(){
        return Bullet::getInstance((getX() + 60), (getY() + 40), 100, 20, "laser2.png", 20, false);
    }

    void Enemy::moveLeft(){
        int value = -1 * SPEED;
        setX(value);
    
    }

    Component* Enemy::perform(SDL_Event event)
    {
        moveLeft();
        switch (movementPattern){
            case 0: 

                if(movementCounter > 100 && movementCounter <= 200){
                    moveUp();
                } else if (movementCounter <= 100 || (movementCounter > 200 && movementCounter < 300)){
                    moveDown();
                } else {
                    movementCounter = 0;
                }
                movementCounter++;
                break;
            case 1:
                if(movementCounter > 100 && movementCounter <= 200){
                    moveDown();
                } else if (movementCounter <= 100 || (movementCounter > 200 && movementCounter < 300)){
                    moveUp();
                } else {
                    movementCounter = 0;
                }
                movementCounter++;
                break;
            case 2: 
                moveLeft();
                break;
            case 3:
                if(movementCounter < 100){
                    moveUp();
                    moveUp();
                }
                else if(movementCounter > 100 && movementCounter < 200){
                    moveDown();
                    moveDown();
                }
                movementCounter++;
                break; 
        }

        shootingCooldown -= 1;

        
        
        if (shootingCooldown <= 0){
            shootingCooldown = shootingSpeed;
            return shoot();
        }
        return NULL;
    }
}