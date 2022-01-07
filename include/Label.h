#ifndef LABEL_H
#define LABEL_H
#include "Component.h"
namespace space_invaders
{

    class Label : public Component
    {
    public:
        static Label *getInstance(int x, int y, int w, int h, std::string txt);
        void setText(std::string text);
        Component *perform(const std::vector<Component *>& comps) { return NULL; };
        void updateTexture();
        void kill(){};
        void takeDamage(){};
        void removal() { this->~Label(); };
        void draw() const;
        void setColor(SDL_Color col) { color = col; }
        const SDL_Color &getColor() const { return color; };
        const SDL_Color &getOriginalColor() const { return originalColor; };
        std::string getText() const { return text; };
        ~Label();

    protected:
        Label(int x, int y, int w, int h, std::string txt);

    private:
        Label(const Label& background) = delete;
        const Label &operator=(const Label&) = delete;
        std::string text;
        SDL_Texture *texture;
        SDL_Color color;
        SDL_Color originalColor;
    };
}

#endif