#ifndef SPAWNER_H
#define SPAWNER_H

#include "Controller.h"
#include "Session.h"
#include "System.h"

namespace space_invaders
{
    class Spawner
    {
    public:
        static Spawner *getInstance(Session &session);
        ~Spawner();
        void createProtagonist();
        void createEnemies(int amountOfEnemies, int enemyTypes);
        void createDebris(int amountOfDebris, int debrisTypes);
        void createDynamicBackgrounds(int amountOfDynamicBackgrounds, int dynamicBackgroundTypes, int distanceBetweenDynamicBackgrounds);

    protected:
        Spawner(Session &session);

    private:
        Session &session;
        const Controller& controller = sys.get_controller();
    };

extern System sys;
}
#endif