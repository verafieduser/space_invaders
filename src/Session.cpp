#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Background.h"
#include "Collision.h"
#include "Session.h"
#include "System.h"

namespace cwing
{
#define FPS 60;

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

	void Session::remove(Component *c)
	{
		toBeRemoved.push_back(c);
	}

	void Session::run()
	{
		std::random_shuffle(enemies.begin(), enemies.end());

		bool quit = false;
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

			gameActions(event);
			loadPendingComponents();
			removeComponents(comps);
			enemySpawner();

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

			for (Component *c : comps)
			{
				c->draw();
			}

			SDL_RenderPresent(sys.get_ren());
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0)
			{
				SDL_Delay(delay);
			}

		} //yttre while
	}

	Session::~Session()
	{
	}

	void Session::removeComponents(std::vector<Component *> &components){
		removeComponents(components, 0);
	}

	void Session::removeComponents(std::vector<Component *> &components, int offset)
	{
		int counter = 0;
		for (Component *c : toBeRemoved)
		{
			if(counter < offset){
				counter ++;
				continue;
			}
			for (std::vector<Component *>::iterator i = components.begin(); i != components.end();)
			{

				if (*i == c)
				{
					i = components.erase(i);
					delete c;
				}
				else
				{
					i++;
				}
			}
		}
		toBeRemoved.clear();
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
			removeComponents(enemies, currentEnemy+1);
		}

		for (Component *c : gameOverComps)
		{
			add(c);
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

	void Session::gameActions(SDL_Event &event)
	{
		for (Component *c : comps)
		{
			Component *newC = c->perform(event);
			if (newC != NULL)
			{
				add(newC);
			}

			for (Component *c2 : comps)
			{
				if (c != c2 && Collision::canCollide(c, c2))
				{
					c->takeDamage();
					c2->takeDamage();
					//TODO: create damage sprite? takeDamage maybe should return a component?
				}
			}

			if (c->isKilled())
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
				else if (name == "Protagonist")
				{
					gameOver();
					break;
				}
			}
		}
	}

	void Session::enemySpawner()
	{
		int amountOfEnemies = enemies.size();
		spawnCounter++;

		if (spawnCounter > spawnFrequency && amountOfEnemies > 0 && currentEnemy+1 < amountOfEnemies)
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
}