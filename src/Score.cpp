#include "Score.h"
#include <sstream>

namespace space_invaders
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

    Score::~Score()
    {
        SDL_DestroyTexture(texture);
    }

    Component *Score::perform(const std::vector<Component *>& comps)
    {

        int value;
        if (message == "SCORE")
        {
            value = ses.getEnemiesDefeated();
        }
        else if (message == "LEVEL")
        {
            value = ses.getLevel();
            if (value > levelValue)
            {
                newLevel = true;
                levelValue++;
            }
        }
        else if (message == "FINAL SCORE")
        {
            value = ses.getEnemiesDefeated();
        }
        else if (message == "FINAL LEVEL")
        {
            value = ses.getLevel();
        }
        else if (message == "INNOCENT DEBRIS DESTROYED")
        {
            value = ses.getDebrisDestroyed();
        }
        

        std::ostringstream ostr;
        ostr << value;
        setText(message + ": " + ostr.str());

        if (newLevel)
        {

            if (counter == 0)
            {

                setX(showcaseLocation);
                setY(showcaseLocation);
                setW(showcaseW);
                setH(showcaseH);
                setColor({0, 255, 247});
            }
            counter++;

            if (counter == showNewLevelForXFrames)
            {
                newLevel = false;
                counter = 0;
                int restorePosition = showcaseLocation * -1;
                int restoreW = showcaseW * -1;
                int restoreH = showcaseH * -1;
                setX(restorePosition);
                setY(restorePosition);
                setW(restoreW);
                setH(restoreH);
                setColor(getOriginalColor());
            }
        }

        return NULL;
    }
}