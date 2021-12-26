#include "Sprite.h"
#include <SDL2/SDL.h>

namespace cwing
{

    class Protagonist : public Sprite
    {
    public:
        static Protagonist *getInstance(int x, int y, int w, int h, std::string image_path);
        // void moveUp();
        // void moveDown();
        // void moveLeft();
        // void moveRight();
        void spaceDown();
        void updateMovement(Direction dir);
        void perform(SDL_Event event);
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
        Protagonist(int x, int y, int w, int h, std::string images_path);

    private:
        SDL_Texture *texture;
        SDL_Texture *sprite;
    };
}
extern std::string IMAGES_PATH;
