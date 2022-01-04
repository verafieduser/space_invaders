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
        static Protagonist *getInstance(int x, int y, int w, int h, std::string image_path, Controller& controller, Healthbar& healthbar);
        Component *shoot();
        Component *perform(SDL_Event event);
        void setHealthbar(Healthbar *h);
        void takeDamage()
        {
            if (damageCooldown == 0)
            {
                healthbar.updateHealth(-1);
                health--;

            }
            damageCooldown = 60;
        };
        ~Protagonist();

    protected:
        Protagonist(int x, int y, int w, int h, std::string images_path, Controller& controller, Healthbar& healthbar);

    private:
        Protagonist(const Protagonist &protagonist) = delete;
        const Protagonist &operator=(const Protagonist&) = delete;
        int shootingCooldown = 0;
        int damageCooldown = 0;
        Healthbar &healthbar;
        Controller &controller;
    };
}

extern std::string IMAGES_PATH;

#endif