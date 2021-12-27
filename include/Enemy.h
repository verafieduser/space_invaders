#include "Sprite.h"
#include <SDL2/SDL.h>

namespace cwing
{

    class Enemy : public Sprite
    {
    public:
        static Enemy *getInstance(int x, int y, int w, int h, std::string image_path);
        Component* shoot();
        Component* perform(SDL_Event event);
        int movementPattern;
        int movementCounter = 0;
        int shootingSpeed;
        void moveLeft();
        ~Enemy();

    protected:
        Enemy(int x, int y, int w, int h, std::string images_path);

    private:
        int shootingCooldown = 0;
        SDL_Texture *sprite;
    };
}

extern std::string IMAGES_PATH;