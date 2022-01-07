#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"

namespace space_invaders
{

    class Enemy : public Actor
    {
    public:
        static Enemy *getInstance(int x, int y, int w, int h, std::string image_path, int randomSeed);
        Component *shoot();
        Component *perform(const std::vector<Component *>& comps);
        int movementPattern;
        int movementCounter = 0;
        int shootingSpeed;
        void moveLeft();
        ~Enemy();

    protected:
        Enemy(int x, int y, int w, int h, std::string images_path, int randomSeed);

    private:
        Enemy(const Enemy &enemy) = delete;
        const Enemy &operator=(const Enemy &) = delete;
        int shootingCooldown = 0;
    };
}

extern std::string IMAGES_PATH;

#endif