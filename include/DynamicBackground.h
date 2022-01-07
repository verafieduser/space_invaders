#ifndef DYNAMIC_BACKGROUND_H
#define DYNAMIC_BACKGROUND_H

#include "Actor.h"

namespace space_invaders
{
    class DynamicBackground : public Actor
    {
    public:
        static DynamicBackground *getInstance(int x, int y, int w, int h, std::string image_path);
        ~DynamicBackground();
        Component *perform(const std::vector<Component *>& comps);
        void removal() { this->~DynamicBackground(); };
        void draw() const;
        
    protected:
        DynamicBackground(int x, int y, int w, int h, std::string images_path);
        void moveLeft();
    private:
        DynamicBackground(const DynamicBackground &dynamicBackground) = delete;
        const DynamicBackground &operator=(const DynamicBackground &) = delete;
        int speedCounter = 0;
        int moveEveryXFrame;
        std::string imagepath;
    };
}

extern std::string IMAGES_PATH;
extern int SCREEN_WIDTH;

#endif