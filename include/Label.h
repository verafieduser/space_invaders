#ifndef LABEL_H
#define LABEL_H
#include "Component.h"
namespace space_invaders
{

    class Label : public Component
    {
    public:
        static Label *getInstance(int x, int y, int w, int h, std::string txt);
        ~Label();
        Component *perform(const std::vector<Component *> &comps) { return NULL; };
        void removal() { this->~Label(); };

    protected:
        Label(int x, int y, int w, int h, std::string txt);
        void setColor(SDL_Color col) { color = col; };
        const SDL_Color &getColor() const { return color; };
        const SDL_Color &getOriginalColor() const { return originalColor; };
        void setText(std::string text);
        void updateTexture();

    private:
        Label(const Label &background) = delete;
        const Label &operator=(const Label &) = delete;
        std::string text;
        SDL_Color color, originalColor;
    };
}

#endif