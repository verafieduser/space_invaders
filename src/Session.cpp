#include <iostream>
#include <algorithm>
#include <sstream>
#include "Collision.h"
#include "Session.h"

#define FPS 60;
namespace space_invaders
{
	Session::~Session()
	{
		//TODO: should we have something here perhaps?
		//remove vectors one by one
		//comps, toBeRemoved, toBeAdded, enemies, gameOverComps;
		loadPendingComponents();
		for (Component *c : comps)
		{
			remove(c);
		}
		for (Component *c : enemies)
		{
			remove(c);
		}
		for (Component *c : gameOverComps)
		{
			remove(c);
		}

		removeComponents(toBeAdded);
		removeComponents(enemies);
		removeComponents(gameOverComps);
	}

	void Session::add(Component *c)
	{
		toBeAdded.push_back(c);
	}

	void Session::addEnemyTypes(Component *c)
	{
		enemies.push_back(c);
	}

	void Session::addGameOverComps(Component *c)
	{
		gameOverComps.push_back(c);
	}

	void Session::run()
	{
		//TODO: this should maybe be in main? or a function that can be called from main atleast?
		std::random_shuffle(enemies.begin(), enemies.end());

		//controller = sys.get_controller();

		bool quit = false;
		//bool pause = false;
		const int tickInterval = 1000 / FPS;
		while (!quit)
		{
			Uint32 nextTick = SDL_GetTicks() + tickInterval;
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				}
			}

			// // something like this if we want a pause function. we could use the same method to implement other system functions, like a settings meny.
			// const Uint8* state = controller->getKeyboardState();
			// if (state[SDL_SCANCODE_ESCAPE]){
			// 	pause = true;
			// 	while (pause){

			// 		loadPendingComponents();
			// 		removeComponents(comps); // clears current game stuff
			// 		for(Component *c : pauseComps){
			// 			add(c);
			// 		}
			// 		render(pauseComps);	// only renders what is paused, rest is still.
			// 		state = controller->getState();	//not sure which state it should be yet
			// 		if(state[x]){
			// 			pause = false;
			// 			for(Component *c : pauseComps){
			// 				remove(c);
			// 			}	//removes pause comps from the game loop, but makes sure to not delete them.
			// 			removeComponents(pauseComps, 0, true);
			// 		}
			// 	}
			// }
			gameActions();
			loadPendingComponents();
			removeComponents(comps);
			enemySpawner();
			render(comps);
			delayToNextTick(nextTick);

		} //yttre while
		cleanUp();
	}

	void Session::remove(Component *c)
	{
		toBeRemoved.push_back(c);
	}

	void Session::removeComponents(std::vector<Component *> &components)
	{
		removeComponents(components, 0, false);
	}

	void Session::removeComponents(std::vector<Component *> &components, int offset, bool dontDelete)
	{
		int counter = 0;
		for (Component *c : toBeRemoved)
		{
			if (counter < offset)
			{
				counter++;
				continue;
			}
			for (std::vector<Component *>::iterator i = components.begin(); i != components.end();)
			{

				if (*i == c)
				{
					i = components.erase(i);
					if (!dontDelete)
					{
						delete c;
					}
				}
				else
				{
					i++;
				}
			}
		}
		toBeRemoved.clear();
	}

	void Session::render(std::vector<Component *> &components)
	{
		int success = SDL_SetRenderDrawColor(sys.get_ren(), 0, 0, 0, 0);
		if (success < 0)
		{
			std::cout << SDL_GetError() << " Error in SetRenderDrawColor \n";
		}

		success = SDL_RenderClear(sys.get_ren());
		if (success < 0)
		{
			std::cout << SDL_GetError() << " Error in RenderClear \n";
		}

		for (Component *c : components)
		{
			c->draw();
		}

		SDL_RenderPresent(sys.get_ren());
	}

	void Session::delayToNextTick(Uint32 nextTick)
	{
		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
		{
			SDL_Delay(delay);
		}
	}

	void Session::gameOver()
	{
		loadPendingComponents();
		for (Component *c : comps)
		{
			std::string name = c->getName();
			//TODO: could be a vector of names added from main, for objects that should be exempt?
			if (name != "DynamicBackground" && name != "Background" && name != "Label")
			{
				remove(c);
			}
		}

		removeComponents(comps);

		//Makes sure spawning stops if you lose, if that setting is added.
		if (!spawningToContinueAfterDeath)
		{
			for (Component *c : enemies)
			{
				remove(c);
			}
			removeComponents(enemies, currentEnemy + 1, false);
		}

		for (Component *c : gameOverComps)
		{
			add(c);
		}
	}

	void Session::gameActions()
	{
		for (Component *c : comps)
		{
			Component *newC = c->perform(comps);
			if (newC != NULL)
			{
				add(newC);
			}

			// damageCalculation(c);

			if (c->isKilled())
			{
				deathCalculation(c);
				if (c->getName() == "Protagonist")
				{
					gameOver();
					break;
				}
			}
		}
	}

	void Session::loadPendingComponents()
	{
		for (Component *c : toBeAdded)
		{
			comps.push_back(c);
		}
		toBeAdded.clear();
	}

	void Session::enemySpawner()
	{
		int amountOfEnemies = enemies.size();
		spawnCounter++;

		if (spawnCounter > spawnFrequency && amountOfEnemies > 0 && currentEnemy + 1 < amountOfEnemies)
		{
			spawnCounter = 0;

			currentEnemy++;

			//LEVEL ADVANCEMENT:
			if (currentEnemy % newLevelEveryXSpawn == 0)
			{
				spawnFrequency = spawnFrequency / levelDifficultyIncrease;
				level++;

				spawnCounter = betweenLevels * 1;
			}

			//WIN STATE:
			if (amountOfEnemies == currentEnemy)
			{
			}

			add(enemies.at(currentEnemy));
		}
	}

	void Session::deathCalculation(Component *c)
	{
		remove(c);
		//TODO: consider ways to make which names lead to what behaviour added from main instead of
		std::string name = c->getName();
		if (name == "Defeated enemy")
		{
			enemiesDefeated++;
		}
		else if (name == "Destroyed debris")
		{
			debrisDestroyed++;
		}
	}

	void Session::cleanUp()
	{
		sys.~System();
		this->~Session();
	}
}