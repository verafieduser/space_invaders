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
        void perform(SDL_Event event);
        ~Protagonist();

    protected:
        Protagonist(int x, int y, int w, int h, std::string images_path);

    private:
        SDL_Texture *texture;
        SDL_Texture *sprite;
    };
}
extern std::string IMAGES_PATH;
