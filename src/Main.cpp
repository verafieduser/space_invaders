#include <SDL2/SDL.h>
#include "Background.h"
#include "Session.h"
#include "Score.h"
#include "System.h"
#include "Spawner.h"

using namespace space_invaders;

Session ses;
int amountOfEnemiesToSpawn = 100;
int amountOfDebrisToSpawn = 200;
int amountOfDynamicBackgroundsToSpawn = 30;
int amountOfLevels = 4;
int enemyTypes = 5;
int debrisTypes = 7;
int dynamicBackgroundTypes = 8;
int distanceBetweenDynamicBackgrounds = 1800;

int main(int argc, char **argv)
{

	

	//sets how many frames it should take until sprites start spawning upon game start
	ses.setInitialWait(200);

	//sets how much faster enemies should spawn for each level increase
	ses.setLevelDifficultyIncrease(1.8);

	//decides how many enemies and debris you need to survive before you proceed to the next level
	ses.setNewLevelEveryXSpawn((amountOfEnemiesToSpawn + amountOfDebrisToSpawn) / amountOfLevels + 1);

	//sets how often (every x frame) sprites should spawn: 
	ses.setSpawnFrequency(50);

	//sets how many frames of wait there should be until the next level starts spawning enemies
	ses.setWaitBetweenLevels(300);

	//decides whether enemies should keep spawning over the game over screen
	ses.setSpawningToContinueAfterDeath(false);

	//components to be displayed upon game over
	ses.addGameOverComps(Label::getInstance(530, 200, 500, 70, "Game Over"));
	ses.addGameOverComps(Score::getInstance(620, 500, 300, 35, "FINAL SCORE", ses));
	ses.addGameOverComps(Score::getInstance(530, 600, 500, 30, "INNOCENT DEBRIS DESTROYED", ses));
	sys.addBackgroundMusic(SOUNDS_PATH + "music.wav");


	//Background image
	Background *bg = Background::getInstance(1600, 720, "bg.png");
	ses.add(bg);

	//Spawning of sprites:
	Spawner *spawner = Spawner::getInstance(ses);
	spawner->createDynamicBackgrounds(amountOfDynamicBackgroundsToSpawn, dynamicBackgroundTypes, distanceBetweenDynamicBackgrounds);
	spawner->createProtagonist();
	spawner->createEnemies(amountOfEnemiesToSpawn, enemyTypes);
	spawner->createDebris(amountOfDebrisToSpawn, debrisTypes);

	//Creating labels that display the current score and level
	Score *score = Score::getInstance(250, 20, 200, 30, "SCORE", ses);
	ses.add(score);

	Score *level = Score::getInstance(500, 20, 200, 30, "LEVEL", ses);
	ses.add(level);


	//adds names that the engine checks against to give score up, or game over, or save from destruction:
	std::vector<std::string> namesExemptFromGameOverDestruction;
	namesExemptFromGameOverDestruction.push_back("Dynamic Background");
	namesExemptFromGameOverDestruction.push_back("Background");
	namesExemptFromGameOverDestruction.push_back("Label");
	std::vector<std::string> componentNamesThatGiveScoreUponKill;
	componentNamesThatGiveScoreUponKill.push_back("Defeated enemy");
	std::vector<std::string> componentNamesThatGiveSecondaryScoreUponKill;
	componentNamesThatGiveSecondaryScoreUponKill.push_back("Destroyed debris");

	ses.setNamesExemptFromGameOverDestruction(namesExemptFromGameOverDestruction);
	ses.setNameOfComponentThatCauseGameOverUponKill("Protagonist");
	ses.setNamesOfComponentsThatGiveScoreUponKill(componentNamesThatGiveScoreUponKill);
	ses.setNamesOfComponentsThatGiveSecondaryScoreUponKill(componentNamesThatGiveSecondaryScoreUponKill);


	ses.run();

	return 0;
}

// TODO: EXIT_SUCCESS EXIT_FAILURE?