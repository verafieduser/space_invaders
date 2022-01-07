#ifndef DEBRIS_H
#define DEBRIS_H

#include "Actor.h"

namespace space_invaders
{
    class Debris : public Actor
    {
    public:
        static Debris *getInstance(int x, int y, int w, int h, std::string image_path, int speed, short int health);
        ~Debris();
        Component *perform(const std::vector<Component *>& comps);
        void draw() const;

    protected:
        Debris(int x, int y, int w, int h, std::string images_path, int speed, short int health);
        void moveLeft();
        
    private:
        Debris(const Debris& debris) = delete;
        const Debris &operator=(const Debris &) = delete;
        
        void spinDebris(const int &speed);
        void setAngle(const int &angle);

        float angle = 0;
        int spinDir, spinEveryXFrame, spinCounter;

    };
}

extern std::string IMAGES_PATH;

#endif
