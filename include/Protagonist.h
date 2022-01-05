#ifndef PROTAGONIST_H
#define PROTAGONIST_H

#include "Sprite.h"
#include "Healthbar.h"
#include "Controller.h"

namespace space_invaders
{

    class Protagonist : public Sprite
    {
    public:
        static Protagonist *getInstance(int x, int y, int w, int h, std::string image_path, Controller &controller, Healthbar &healthbar);
        Component *shoot();
        Component *perform(std::vector<Component *>& comps);
        void setHealthbar(Healthbar *h);
        const int getDamageCooldown();
        void takeDamage();
        ~Protagonist();

    protected:
        Protagonist(int x, int y, int w, int h, std::string images_path, Controller &controller, Healthbar &healthbar);

    private:
        Protagonist(const Protagonist &protagonist) = delete;
        const Protagonist &operator=(const Protagonist &) = delete;
        int shootingCooldown = 0;
        int damageCooldown = 0;
        Healthbar &healthbar;
        Controller &controller;
    };
}

extern std::string IMAGES_PATH;

#endif