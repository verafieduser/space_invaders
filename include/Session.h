#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <vector>
#include "Component.h"
#include <SDL2/SDL.h>
#include "Label.h"

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
		void gameOver();
		void gameActions(SDL_Event &event);
		void loadPendingComponents();
		void removeComponents();
		void enemySpawner();
		void setInitialWait(int initialWait) {spawnCounter = initialWait;};
		void setWaitBetweenLevels(int waitBetweenLevels) {betweenLevels = waitBetweenLevels;};
		void setSpawnFrequency(int spawnFreq) {spawnFrequency = spawnFreq;};
		void setLevelDifficultyIncrease(float levelDifficultyInc) {levelDifficultyIncrease = levelDifficultyInc;};
		void setSpawningToContinueAfterDeath(bool toContinue) {spawningToContinueAfterDeath = toContinue;};
		~Session();

	private:
		std::vector<Component *> comps, toBeRemoved, toBeAdded, enemies, gameOverComps;
		Label *scoreLabel = Label::getInstance(250, 20, 200, 30, "SCORE: 0");
		Label *levelLabel = Label::getInstance(500, 20, 200, 30, "Level 1");
		int betweenLevels = 100;
		int spawnCounter = -100;
		int spawnFrequency = 60;
		float levelDifficultyIncrease = 1.5;
		bool spawningToContinueAfterDeath = true;

	};

}

extern std::string IMAGES_PATH;
extern std::string SOUNDS_PATH;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#endif