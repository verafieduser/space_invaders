#include "Background.h"

namespace space_invaders
{
    Background::Background(int w, int h, std::string background_image_path) : Component(0,
                                                                                        0, w, h)
    {
        bg_tex = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + background_image_path).c_str());
        collidable = false;
        name = "Background";
    }
    
    Background *Background::getInstance(int w, int h, std::string background_image_path)
    {
        return new Background(w, h, background_image_path);
    }

    Background::~Background()
    {
        SDL_DestroyTexture(bg_tex);
    }

    // Component *Background::perform(std::vector<Component *> c)
    // {
    //     return NULL;
    // }

    void Background::kill() {}

    void Background::draw() const
    {
        SDL_RenderCopy(sys.get_ren(), bg_tex, NULL, &getRect());
    }
}