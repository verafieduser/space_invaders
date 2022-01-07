#ifndef SCORE_H
#define SCORE_H

#include "Label.h"
#include "Component.h"
#include "System.h"
#include "Session.h"

namespace space_invaders
{
    class Score : public Label
    {
    public:
        static Score *getInstance(int x, int y, int w, int h, std::string txt, Session &session);
        Component *perform(const std::vector<Component *>& comps);
        void removal() { this->~Score(); };
        ~Score();

    protected:
        Score(int x, int y, int w, int h, std::string txt, Session &session);

    private:
        Score(const Score& background) = delete;
        const Score &operator=(const Score&) = delete;
        std::string text, message;
        SDL_Texture *texture;
        bool newLevel = false;
        int showNewLevelForXFrames = 360;
        Session &ses;
        int counter, levelValue = 0;
        int showcaseLocation = 100;
        int showcaseW = 200;
        int showcaseH = 50;
        int originalW, originalH;
    };

    extern int SCREEN_WIDTH;
    extern int SCREEN_HEIGHT;
}

#endif