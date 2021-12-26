#include "Debris.h"
#include "Sprite.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <SDL2/SDL_image.h>

namespace cwing
{

    Debris::Debris(int x, int y, int w, int h, std::string image_path, Session &session, int speed) : Sprite(x, y, w, h, image_path, session)
    {
        sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
        SPEED = speed;
    }

    Debris::~Debris()
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(sprite);
    }

    Debris *Debris::getInstance(int x, int y, int w, int h, std::string image_path, Session &session, int speed)
    {
        return new Debris(x, y, w, h, image_path, session, speed);
    }

    void Debris::moveLeft()
    {
        int value = -1 * SPEED;
        setX(value);
    }

    void Debris::spinDebris(const int &speed)
    {
        //TODO: randomize spin direction!
        if(angle > 360){
            angle = 0;
        }
        setAngle(angle + speed);
    }

    void Debris::setAngle(const int &newAngle)
    {
        angle = newAngle;
    }

    Component* Debris::perform(SDL_Event event)
    {

        moveLeft();
        spinDebris(SPEED);

        if (isOutOfBoundsLeft())
        {
            kill();
        }
        
        return NULL;
    }

    void Debris::draw() const
    {
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

        SDL_RenderCopyEx(sys.get_ren(), sprite, NULL, &getRect(), angle, NULL, flip);

        SDL_RenderCopyEx(sys.get_ren(), texture, NULL, &getRect(), angle, NULL, flip);
    }
}