#ifndef BULLET_H
#define BULLET_H

#include "Actor.h"

namespace space_invaders
{
    class Bullet : public Actor
    {
    public:
        static Bullet *getInstance(int x, int y, int w, int h, std::string image_path, int speed, bool isFromProtagonist);
        ~Bullet();
        Component *perform(const std::vector<Component *>& c);
        bool fromProtagonist(){return isProtagonistBullet;};
        
    protected:
        Bullet(int x, int y, int w, int h, std::string images_path, int speed, bool isProtagonist);
        Bullet(const Bullet &bullet) = delete;
        const Bullet &operator=(const Bullet &) = delete;
        
        void moveRight();
        void moveLeft();
        
    private:

        Direction dir;
        bool isProtagonistBullet;
    };
}

extern std::string IMAGES_PATH;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#endif