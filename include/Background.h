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
        void removal() { this->~Background(); };

    protected:
        Background(int w, int h, std::string background_image_path);

    private:
        Background(const Background &background) = delete;
        const Background &operator=(const Background &) = delete;
    };
}

extern std::string IMAGES_PATH;

#endif
