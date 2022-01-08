#ifndef PROTAGONIST_H
#define PROTAGONIST_H

#include "Actor.h"
#include "Healthbar.h"
#include "Controller.h"

namespace space_invaders
{

    class Protagonist : public Actor
    {
    public:
        static Protagonist *getInstance(int x, int y, int w, int h, std::string image_path, Controller &controller, Healthbar &healthbar);
        ~Protagonist();
        Component *shoot();
        Component *perform(const std::vector<Component *> &comps);
        void setHealthbar(Healthbar *h);
        const int getDamageCooldown();
        void takeDamage();

    protected:
        Protagonist(int x, int y, int w, int h, std::string images_path, Controller &controller, Healthbar &healthbar);

    private:
        Protagonist(const Protagonist &protagonist) = delete;
        const Protagonist &operator=(const Protagonist &) = delete;
        Component *protagonistControl();
        int shootingCooldown = 0;
        int damageCooldown = 0;
        Healthbar &healthbar;
        Controller &controller;
    };
}

extern std::string IMAGES_PATH;

#endif