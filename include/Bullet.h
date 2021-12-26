#ifndef BULLET_H
#define BULLET_H

#include "Sprite.h"
#include "Session.h"
#include <SDL2/SDL.h>
#include <string>

namespace cwing
{
    class Bullet : public Sprite
    {
    public:
        enum Direction
        {
            RIGHT
        };
        static Bullet *getInstance(int x, int y, int w, int h, std::string image_path, Session &session, int speed);
        int SPEED = 40;
        const bool isOutOfBounds();
        const bool isMovementAllowed(Direction dir);
        Component* perform(SDL_Event event);
        // void draw() const;
        ~Bullet();

    protected:
        Bullet(int x, int y, int w, int h, std::string images_path, Session &session, int speed);

    private:
        SDL_Texture *texture;
        SDL_Texture *sprite;
    };
}

extern std::string IMAGES_PATH;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#endif