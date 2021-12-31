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
        static Bullet *getInstance(int x, int y, int w, int h, std::string image_path, int speed, bool isFromProtagonist);
        int SPEED = 40;
        Direction dir;
        void moveRight();
        void moveLeft();
        bool isFromProtagonist() const { return isProtagonistBullet; };
        Component* perform(SDL_Event event);
        ~Bullet();

    protected:
        Bullet(int x, int y, int w, int h, std::string images_path, int speed, bool isProtagonist);

    private:
        SDL_Texture *sprite;
        bool isProtagonistBullet;
    };
}

extern std::string IMAGES_PATH;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#endif