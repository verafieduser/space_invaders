#ifndef LABEL_H
#define LABEL_H
#include "Component.h"
#include <string>
#include <SDL2/SDL.h>
#include "System.h"
#include "Session.h"
namespace cwing
{

    class Label : public Component
    {
    public:
        static Label *getInstance(int x, int y, int w, int h, std::string txt);
        void setText(std::string text);
        Component *perform(SDL_Event event) { return NULL; };
        void updateTexture();
        void kill(){};
        void takeDamage(){};
        void removal() { this->~Label(); };
        void draw() const { SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect()); }
        void setColor(SDL_Color col) { color = col; }
        const SDL_Color &getColor() const { return color; };
        const SDL_Color &getOriginalColor() const { return originalColor; };
        std::string getText() const { return text; };
        ~Label();

    protected:
        Label(int x, int y, int w, int h, std::string txt);

    private:
        std::string text;
        SDL_Texture *texture;
        SDL_Color color;
        SDL_Color originalColor;
    };
}

#endif