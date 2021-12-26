#include "Sprite.h"
#include "Session.h"
#include <SDL2/SDL.h>

namespace cwing
{

    class Protagonist : public Sprite
    {
    public:
        static Protagonist *getInstance(int x, int y, int w, int h, std::string image_path, Session &session);
        // void moveUp();
        // void moveDown();
        // void moveLeft();
        // void moveRight();
        Component* shoot();
        Component* perform(SDL_Event event);
        void updateMovement(Direction dir);
        ~Protagonist();

        //bool states[4] ={false,false,false,false};
        struct Keystates
		{
			bool left = false;
			bool right = false;
			bool up = false;
			bool down = false;
		};

		Keystates keystates;

    protected:
        Protagonist(int x, int y, int w, int h, std::string images_path, Session &session);

    private:
        int shootingCooldown = 0;
        SDL_Texture *texture;
        SDL_Texture *sprite;
    };
}

extern std::string IMAGES_PATH;
