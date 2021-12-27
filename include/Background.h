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
        static Background *getInstance(int w, int h);
        virtual ~Background();
        Component* perform(SDL_Event event);
        void removal() {this->~Background();}; 
        void draw() const;
        void tick() const;

    protected:
        Background(int w, int h);

    private:
        SDL_Texture *bg_tex;
    };
}

extern std::string IMAGES_PATH;

#endif
