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
#include "System.h"
#include <sstream>
#include <time.h>
#include "DynamicBackground.h"

// Paths to resource folders. Change to your own path!
//std::string resPath = "./resources/";

using namespace std;
using namespace cwing;

Session ses;
int amountOfEnemiesToSpawn = 100;
int amountOfDebrisToSpawn = 200;
int amountOfDynamicBackgroundsToSpawn = 30;
int enemyTypes = 5;
int debrisTypes = 7;
int dynamicBackgroundTypes = 8;
int distanceBetweenDynamicBackgrounds = 1800;

int main(int argc, char **argv)
{
	ses.setInitialWait(200);
	ses.setLevelDifficultyIncrease(1.8);
	ses.setSpawnFrequency(50);
	ses.setWaitBetweenLevels(300);
	ses.addGameOverComps(Label::getInstance(650, 200, 400, 70, "Game Over"));
	sys.addBackgroundMusic(SOUNDS_PATH + "music.wav");

	Background *bg = Background::getInstance(1600, 720, "bg.png");
	ses.add(bg);

	int backgroundType = 1;
	int distance = 800;
	for(int i = 0; i < amountOfDynamicBackgroundsToSpawn; i++){
		srand(i);
		int size = (rand() % 1000) + 400;
		std::ostringstream ostr; 

		ostr << backgroundType;
		ses.add(DynamicBackground::getInstance(distance, 0, size, size, "db" + ostr.str() + ".png"));
		backgroundType++;
		if(backgroundType > dynamicBackgroundTypes){
			backgroundType = 1;
		}
		distance += distanceBetweenDynamicBackgrounds;
	}

	Protagonist *protagonist = Protagonist::getInstance(200, 200, 100, 100, "protagonist.png");
	Healthbar *healthbar = Healthbar::getInstance(20, 20, 200, 80, "full_health.png", "half_health.png", "low_health.png");
	
	protagonist->setHealthbar(healthbar);

	ses.add(protagonist);
	ses.add(healthbar);

	int enemyType = 1;
	for (int i = 1; i <= amountOfEnemiesToSpawn; i++)
	{
		srand(i);
		std::ostringstream ostr;
		//convertion of i into string for usage in enemy creation.
		ostr << enemyType;
		ses.addEnemyTypes(Enemy::getInstance(1800, rand() % 600 + 100, 100, 100, "enemy" + ostr.str() + ".png", rand()));
		enemyType++;
		if (enemyType > enemyTypes)
		{
			enemyType = 1;
		}
	}

//TODO: make bigger debris stronger and more hp, smaller faster and less hp
	int debrisType = 1;
	for (int i = 1; i <= amountOfDebrisToSpawn; i++)
	{
		srand(i);
		int size = (rand() % 200) + 30;
		std::ostringstream ostr;
		ostr << debrisType;
		ses.addEnemyTypes(Debris::getInstance(1800, rand() % 600 + 100, size, size, "asteroid" + ostr.str() + ".png", rand() % 15));
		debrisType++;
		if (debrisType > debrisTypes)
		{
			debrisType = 1;
		}
	}

	ses.run();

	return 0;
}



// #include <iostream>
// #include <string>

// // Alla dessa SDL inkluderingsfiler används inte i detta testprogram.
// // Bifogas endast för test av SDL installation!

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_ttf.h>

// //#define FPS 60

// int main(int argc, char *argv[])
// {

// 	// Paths to resources
// 	//std::string imagePath = "../../images/";
// 	std::string imagePath = "./images/";

// 	//std::string fontPath = "../../fonts/";
// 	std::string fontPath = "./fonts/";

// 	//std::string soundPath = "../../sounds/";
// 	std::string soundPath = "./sounds/";

// 	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
// 	{
// 		std::cout << "Error SDL2 Initialization : " << SDL_GetError();
// 		return EXIT_FAILURE;
// 	}

// 	if (TTF_Init() < 0)
// 	{
// 		std::cout << "Error SDL_ttf Initialization : " << SDL_GetError();
// 		return EXIT_FAILURE;
// 	}

// 	SDL_Window *window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 720, 0);
// 	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

// 	std::cout << (imagePath + "bg.jpg").c_str() << std::endl;

// 	SDL_Surface *bg_sur = IMG_Load((imagePath + "bg.png").c_str());

// 	SDL_Texture *bg_tex = SDL_CreateTextureFromSurface(renderer, bg_sur);
// 	SDL_FreeSurface(bg_sur);

// 	std::cout << "Avsluta programmet genom \"quit\" från fönstrets meny eller genom att stänga fönstret!" << std::endl;

// 	//The background scrolling offset
// 	// int scrollingOffset = 0;

// 	// Loop till dess att programmet avslutas!
// 	bool running = true;
// 	while (running)
// 	{
// 		SDL_Event e;
// 		if (SDL_PollEvent(&e))
// 		{
// 			if (e.type == SDL_QUIT)
// 			{
// 				running = false;
// 			}
// 		}

// 		SDL_RenderClear(renderer);
// 		SDL_RenderCopy(renderer, bg_tex, NULL, NULL);
// 		SDL_RenderPresent(renderer);
// 	}

// 	// Städa innan programmet avslutas!

// 	SDL_DestroyTexture(bg_tex);
// 	SDL_DestroyRenderer(renderer);
// 	SDL_DestroyWindow(window);

// 	TTF_Quit();
// 	SDL_Quit();

// 	return EXIT_SUCCESS;
// }