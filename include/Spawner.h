#ifndef SPAWNER_H
#define SPAWNER_H

#include "Controller.h"
#include "Session.h"
#include "System.h"
#include <vector>

namespace cwing {


    class Spawner {
        public: 
            ~Spawner();
            static Spawner* getInstance(System& system, Session& session);
            void createProtagonist();
            void createEnemies(int amountOfEnemies, int enemyTypes);
            void createDebris(int amountOfDebris, int debrisTypes);
            void createDynamicBackgrounds(int amountOfDynamicBackgrounds, int dynamicBackgroundTypes, int distanceBetweenDynamicBackgrounds);
        protected:
            Spawner(System& system, Session& session);

        private:
            Session& session;
            System& system;
    };
}
#endif