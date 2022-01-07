#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"

namespace space_invaders
{

    class Enemy : public Actor
    {
    public:
        static Enemy *getInstance(int x, int y, int w, int h, std::string image_path, int randomSeed);
        ~Enemy();
        Component *perform(const std::vector<Component *>& comps);
        
    protected:
        Enemy(int x, int y, int w, int h, std::string images_path, int randomSeed);
        void moveLeft();

    private:
        Enemy(const Enemy &enemy) = delete;
        const Enemy &operator=(const Enemy &) = delete;
        Component *shoot();
        int shootingCooldown, movementCounter = 0;
        int movementPattern, shootingSpeed;
        void enemyMovementPattern();
    };
}

extern std::string IMAGES_PATH;

#endif