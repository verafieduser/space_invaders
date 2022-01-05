#ifndef DYNAMIC_BACKGROUND_H
#define DYNAMIC_BACKGROUND_H

#include "Sprite.h"

namespace space_invaders
{
    class DynamicBackground : public Sprite
    {
    public:
        static DynamicBackground *getInstance(int x, int y, int w, int h, std::string image_path);
        Component *perform(std::vector<Component *>& comps);
        void moveLeft();
        void removal() { this->~DynamicBackground(); };
        void draw() const;
        void setAngle(const int &angle);
        void spinImage(int &SPEED);
        ~DynamicBackground();

    protected:
        DynamicBackground(int x, int y, int w, int h, std::string images_path);

    private:
        DynamicBackground(const DynamicBackground &dynamicBackground) = delete;
        const DynamicBackground &operator=(const DynamicBackground &) = delete;
        int speedCounter = 0;
        int moveEveryXFrame, spinDir;
        float angle = 0;
        std::string imagepath;
    };
}

extern std::string IMAGES_PATH;
extern int SCREEN_WIDTH;

#endif