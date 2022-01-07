#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Component.h"
#include "System.h"
#include <SDL2/SDL_image.h>

namespace space_invaders
{
    class Background : public Component
    {
    public:
        static Background *getInstance(int w, int h, std::string background_image_path);
        virtual ~Background();
        Component *perform(const std::vector<Component *> &comps) { return NULL; };
        void removal() { this->~Background(); };
        void draw() const;
        void takeDamage(){};
        void kill();
        void tick() const;

    protected:
        Background(int w, int h, std::string background_image_path);

    private:
        SDL_Texture *bg_tex;
        Background(const Background &background) = delete;
        const Background &operator=(const Background &) = delete;
    };
}

extern std::string IMAGES_PATH;

#endif
