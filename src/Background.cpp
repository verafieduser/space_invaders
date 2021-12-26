#include "Background.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <SDL2/SDL_image.h>
namespace cwing
{

    Background::Background(int w, int h) : Component(0,
                                                     0, w, h)
    {
        //SDL_Surface *bg_sur = IMG_Load((imagesPath + "bg.png").c_str());
        bg_tex = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + "bg.png").c_str());
        //bg_tex = IMG_LoadTexture(sys.get_ren(), (imagesPath + "bg.png").c_str());
    }

    Background::~Background()
    {
        SDL_DestroyTexture(bg_tex);
    }

    Background *Background::getInstance(int w, int h)
    {
        return new Background(w, h);
    }

    void Background::perform(SDL_Event event)
    {
    }

    void Background::draw() const
    {
        SDL_RenderCopy(sys.get_ren(), bg_tex, NULL, &getRect());
    }
}