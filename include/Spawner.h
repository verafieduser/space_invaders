#ifndef SPAWNER_H
#define SPAWNER_H

#include "Controller.h"
#include "Session.h"
#include "System.h"
#include <vector>

namespace cwing
{
    class Spawner
    {
    public:
        ~Spawner();
        static Spawner *getInstance(Controller &controller, Session &session);
        void createProtagonist();
        void createEnemies(int amountOfEnemies, int enemyTypes);
        void createDebris(int amountOfDebris, int debrisTypes);
        void createDynamicBackgrounds(int amountOfDynamicBackgrounds, int dynamicBackgroundTypes, int distanceBetweenDynamicBackgrounds);

    protected:
        Spawner(Controller &controller, Session &session);

    private:
        Session &session;
        Controller& controller;
    };
}
#endif