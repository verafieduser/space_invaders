#include "Label.h"
#include "Component.h"
#include <string>
#include <SDL2/SDL.h>
#include "System.h"
#include "Session.h"
#include <sstream>
namespace cwing
{
    class Score : public Label
    {
    public:
        static Score *getInstance(int x, int y, int w, int h, std::string txt, Session &session);

        Component *perform(SDL_Event event)
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
                    int restorePosition = showcaseLocation*-1;
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
        };
        void removal() { this->~Score(); };
        ~Score();

    protected:
        Score(int x, int y, int w, int h, std::string txt, Session &session);

    private:
        std::string text;
        std::string message;
        SDL_Texture *texture;
        bool newLevel = false;
        int showNewLevelForXFrames = 360;
        Session &ses;
        int counter = 0;
        int levelValue = 0;
        int showcaseLocation = 100;
        int showcaseW = 200;
        int showcaseH = 50;
        int originalW, originalH;

    };

    extern int SCREEN_WIDTH;
    extern int SCREEN_HEIGHT;
}
