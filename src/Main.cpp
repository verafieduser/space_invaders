#include <SDL2/SDL.h>
#include "Background.h"
#include "Label.h"
#include "Session.h"
#include "Button.h"
#include "Sprite.h"
#include "Debris.h"
#include "Protagonist.h"
#include <string>
#include <iostream>
#include "Bullet.h"
#include "Enemy.h"
#include "Healthbar.h"
#include "Score.h"
#include "System.h"
#include <sstream>
#include <time.h>
#include "DynamicBackground.h"
#include "Controller.h"
#include "Spawner.h"

// Paths to resource folders. Change to your own path!
//std::string resPath = "./resources/";

using namespace std;
using namespace cwing;

Session ses;
int amountOfEnemiesToSpawn = 300;
int amountOfDebrisToSpawn = 600;
int amountOfDynamicBackgroundsToSpawn = 30;
int amountOfLevels = 10;
int enemyTypes = 5;
int debrisTypes = 7;
int dynamicBackgroundTypes = 8;
int distanceBetweenDynamicBackgrounds = 1800;

int main(int argc, char **argv)
{
	ses.setInitialWait(200);
	ses.setLevelDifficultyIncrease(1.8);
	ses.setNewLevelEveryXSpawn((amountOfEnemiesToSpawn+amountOfDebrisToSpawn)/amountOfLevels+1);
	ses.setSpawnFrequency(50);
	ses.setWaitBetweenLevels(300);
	ses.setSpawningToContinueAfterDeath(false);
	ses.addGameOverComps(Label::getInstance(530, 200, 500, 70, "Game Over"));
	ses.addGameOverComps(Score::getInstance(620, 500, 300, 35, "FINAL SCORE", ses));
	ses.addGameOverComps(Score::getInstance(530, 600, 500, 30, "INNOCENT DEBRIS DESTROYED", ses));
	sys.addBackgroundMusic(SOUNDS_PATH + "music.wav");
									 //TODO: get_controller should maybe be &?
	
	Background *bg = Background::getInstance(1600, 720, "bg.png");
	ses.add(bg);

	Spawner* spawner = Spawner::getInstance(sys, ses);
	spawner->createDynamicBackgrounds(amountOfDynamicBackgroundsToSpawn, dynamicBackgroundTypes, distanceBetweenDynamicBackgrounds);
	spawner->createProtagonist();
	spawner->createEnemies(amountOfEnemiesToSpawn, enemyTypes);
	spawner->createDebris(amountOfDebrisToSpawn, debrisTypes);

	Score *score = Score::getInstance(250, 20, 200, 30, "SCORE", ses);
	ses.add(score);

	Score *level = Score::getInstance(500, 20, 200, 30, "LEVEL", ses);
	ses.add(level);


	ses.run();

	return 0;
}


// TODO: add return EXIT_FAILURE där error händer?:

//if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
// 	{
// 		std::cout << "Error SDL2 Initialization : " << SDL_GetError();
// 		return EXIT_FAILURE;
// 	}

// 	if (TTF_Init() < 0)
// 	{
// 		std::cout << "Error SDL_ttf Initialization : " << SDL_GetError();
// 		return EXIT_FAILURE;
// 	}


//TODO: 	// Städa innan programmet avslutas!

// 	SDL_DestroyTexture(bg_tex);
// 	SDL_DestroyRenderer(renderer);
// 	SDL_DestroyWindow(window);

// 	TTF_Quit();
// 	SDL_Quit();

// 	return EXIT_SUCCESS;
// }