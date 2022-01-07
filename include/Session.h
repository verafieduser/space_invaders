#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Component.h"
#include "System.h"

namespace space_invaders
{

	class Session
	{
	public:
		~Session();
		const int getEnemiesDefeated() const { return enemiesDefeated; };
		const int getDebrisDestroyed() const { return debrisDestroyed; };
		const int getLevel() const { return level; };
		
		void add(Component *c);
		void addEnemyTypes(Component *c);
		void addGameOverComps(Component *c);
		void run();
		void setInitialWait(int initialWait) { spawnCounter = initialWait * -1; };
		void setWaitBetweenLevels(int waitBetweenLevels) { betweenLevels = waitBetweenLevels * -1; };
		void setSpawnFrequency(int spawnFreq) { spawnFrequency = spawnFreq; };
		void setLevelDifficultyIncrease(float levelDifficultyInc) { levelDifficultyIncrease = levelDifficultyInc; };
		void setSpawningToContinueAfterDeath(bool toContinue) { spawningToContinueAfterDeath = toContinue; };
		void setNewLevelEveryXSpawn(int x) { newLevelEveryXSpawn = x; };
		const int getEnemiesDefeated() const { return enemiesDefeated; };
		const int getDebrisDestroyed() const { return debrisDestroyed; };
		const int getLevel() const { return level; };
	private:
		void remove(Component *c);
		void render(std::vector<Component *> &components);
		void delayToNextTick(Uint32 nextTick);
		void gameOver();
		void gameActions();
		void loadPendingComponents();
		void removeComponents(std::vector<Component *> &components);
		void removeComponents(std::vector<Component *> &components, int offset, bool dontDelete);
		void enemySpawner();
		void deathCalculation(Component *c);
		void cleanUp();
		int level = 1;
		float levelDifficultyIncrease = 1;
		bool spawningToContinueAfterDeath = true;
		std::vector<Component *> comps, toBeRemoved, toBeAdded, enemies, gameOverComps;
		int betweenLevels, spawnCounter, currentEnemy, enemiesDefeated, debrisDestroyed, newLevelEveryXSpawn, spawnFrequency = 0;

	};

}

extern std::string IMAGES_PATH;
extern std::string SOUNDS_PATH;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#endif