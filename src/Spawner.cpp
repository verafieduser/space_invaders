#include <sstream>
#include "Spawner.h"
#include "Controller.h"
#include "Protagonist.h"
#include "DynamicBackground.h"
#include "Debris.h"
#include "Enemy.h"

namespace cwing
{
    Spawner::Spawner(System& system, Session &session) : session(session), system(system)
    {
    }
    Spawner::~Spawner() {}
    Spawner *Spawner::getInstance(System& system, Session &session)
    {
        return new Spawner(system, session);
    }
    void Spawner::createProtagonist()
    {
        Healthbar *healthbar = Healthbar::getInstance(20, 20, 200, 80, "full_health.png", "half_health.png", "low_health.png");
        Protagonist *protagonist = Protagonist::getInstance(200, 200, 100, 100, "protagonist.png");
        protagonist->setHealthbar(healthbar);
        Controller* c = system.get_controller();
        protagonist->setController(c);
        session.add(protagonist);
        session.add(healthbar);
    }
    void Spawner::createEnemies(int amountOfEnemies, int enemyTypes)
    {
        	int enemyType = 1;
	for (int i = 1; i <= amountOfEnemies; i++)
	{
		srand(i);
		std::ostringstream ostr;
		ostr << enemyType;
		int size = 100;
		session.addEnemyTypes(Enemy::getInstance(1800, rand() % 620, size, size, "enemy" + ostr.str() + ".png", rand()));
		enemyType++;
		if (enemyType > enemyTypes)
		{
			enemyType = 1;
		}
	}
    }
    void Spawner::createDebris(int amountOfDebris, int debrisTypes) {
        	int debrisType = 1;
	for (int i = 1; i <= amountOfDebris; i++)
	{
		srand(i);
		int size = (rand() % 200) + 30;
		int speed;
		if(size >= 200){
			speed = 1;
		} else if (size >= 170){
			speed = 3;
		} else if(size >= 150){
			speed = 4;
		} else if(size >= 100){
			speed = 5;
		} else if(size >= 80){
			speed = 9;
		} else if (size >= 50){ 
			speed = 12;
		}else if(size >= 30){
			speed = 15;
		}

		std::ostringstream ostr;
		ostr << debrisType;
		session.addEnemyTypes(Debris::getInstance(1800, rand() % 650-30, size, size, "asteroid" + ostr.str() + ".png", speed));
		debrisType++;
		if (debrisType > debrisTypes)
		{
			debrisType = 1;
		}
	}
    }

    void Spawner::createDynamicBackgrounds(int amountOfDynamicBackgrounds, int dynamicBackgroundTypes, int distanceBetweenDynamicBackgrounds)
    {
        int backgroundType = 1;
        int distance = 800;
        for (int i = 0; i < amountOfDynamicBackgrounds; i++)
        {
            srand(i);
            int size = (rand() % 1000) + 400;
            std::ostringstream ostr;

            ostr << backgroundType;
            session.add(DynamicBackground::getInstance(distance, rand() % 300, size, size, "db" + ostr.str() + ".png"));
            backgroundType++;
            if (backgroundType > dynamicBackgroundTypes)
            {
                backgroundType = 1;
            }
            distance += distanceBetweenDynamicBackgrounds;
        }
    }
}