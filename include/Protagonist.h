#ifndef PROTAGONIST_H
#define PROTAGONIST_H

#include "Sprite.h"
#include "Session.h"
#include "Healthbar.h"
#include <SDL2/SDL.h>
#include <string>

namespace cwing
{

    class Protagonist : public Sprite
    {
    public:
        static Protagonist *getInstance(int x, int y, int w, int h, std::string image_path);
        Component* shoot();
        Component* perform(SDL_Event event);
        void setHealthbar(Healthbar *h);
        void takeDamage(){
            if(damageCooldown==0)
            {
                healthbar->updateHealth(-1); 
                health--;
                //shootingCooldown = 10;
                //TODO: some other result from being shot ? also - currently the keyframe refreshes when it shouldnt
            } 
            damageCooldown = 60;};
        ~Protagonist();

    protected:
        Protagonist(int x, int y, int w, int h, std::string images_path);

    private:
        int shootingCooldown = 0;
        int damageCooldown = 0;
        SDL_Texture *sprite;
        Healthbar *healthbar;
    };
}

extern std::string IMAGES_PATH;

#endif