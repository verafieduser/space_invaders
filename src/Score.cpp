#include "Score.h"
#include "Component.h"
#include "Label.h"
#include <string>

namespace cwing
{
    Score::Score(int x, int y, int w, int h, std::string txt, Session &session) : Label(x, y, w, h, txt), ses(session), originalW(w), originalH(h)
    {
        name = "Label";
        collidable = false;
        message = txt;
    }
    Score *Score::getInstance(int x, int y, int w, int h, std::string txt, Session &session)
    {
        return new Score(x, y, w, h, txt, session);
    }

    Score::~Score(){
        SDL_DestroyTexture(texture);
    }
}