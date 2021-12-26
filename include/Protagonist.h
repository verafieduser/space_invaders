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
        void perform(SDL_Event event);
        ~Protagonist();

    protected:
        Protagonist(int x, int y, int w, int h, std::string images_path, Session &session);

    private:
        SDL_Texture *texture;
        SDL_Texture *sprite;
    };
}

extern std::string IMAGES_PATH;
