#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <vector>
#include "Component.h"
#include <SDL2/SDL.h>
#include "Controller.h"
#include "System.h"

namespace cwing
{

	class Session
	{
	public:
		void add(Component *c);
		void addEnemyTypes(Component *c);
		void addGameOverComps(Component *c);
		void remove(Component *c);
		void run();
		void render(std::vector<Component *> &components);
		void delayToNextTick(Uint32 nextTick);
		void gameOver();
		void gameActions(SDL_Event &event);
		void loadPendingComponents();
		void removeComponents(std::vector<Component *>& components);
		void removeComponents(std::vector<Component *>& components, int offset, bool dontDelete);
		void enemySpawner();
		void setInitialWait(int initialWait) {spawnCounter = initialWait *-1;};
		void setWaitBetweenLevels(int waitBetweenLevels) {betweenLevels = waitBetweenLevels *-1;};
		void setSpawnFrequency(int spawnFreq) {spawnFrequency = spawnFreq;};
		void setLevelDifficultyIncrease(float levelDifficultyInc) {levelDifficultyIncrease = levelDifficultyInc;};
		void setSpawningToContinueAfterDeath(bool toContinue) {spawningToContinueAfterDeath = toContinue;};
		void setNewLevelEveryXSpawn(int x) {newLevelEveryXSpawn = x;};
		const int getEnemiesDefeated() const{return enemiesDefeated;};
		const int getDebrisDestroyed() const{return debrisDestroyed;};
		const int getLevel() const{return level;};
		~Session();

	private:
		std::vector<Component *> comps, toBeRemoved, toBeAdded, enemies, gameOverComps;
		int betweenLevels = 0;
		int spawnCounter = 0;
		int spawnFrequency = 60;
		int currentEnemy = 0;
		int enemiesDefeated = 0;
		int debrisDestroyed = 0;
		int level = 1;
		int newLevelEveryXSpawn = 0;
		float levelDifficultyIncrease = 1;
		bool spawningToContinueAfterDeath = true;
		Controller *controller;

	};

}

extern std::string IMAGES_PATH;
extern std::string SOUNDS_PATH;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#endif