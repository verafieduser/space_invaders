#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Component.h"
#include <string>
#include <SDL2/SDL.h>

namespace cwing
{
    class Background : public Component
    {
    public:
        static Background *getInstance(int w, int h, std::string background_image_path);
        virtual ~Background();
        Component *perform(SDL_Event event);
        void removal() { this->~Background(); };
        void draw() const;
        void takeDamage(){};
        void kill();
        void tick() const;

    protected:
        Background(int w, int h, std::string background_image_path);

    private:
        SDL_Texture *bg_tex;
    };
}

extern std::string IMAGES_PATH;

#endif
