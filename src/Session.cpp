#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Background.h"
#include "Collision.h"
#include "Session.h"
#include "System.h"

int spawnCounter = 100;
int howOftenSpawn = 30;
int currentEnemy = 0;

namespace cwing
{
#define FPS 60;

	void Session::add(Component *c)
	{
		toBeAdded.push_back(c);
	}

	void Session::addEnemyTypes(Component *c){
		enemies.push_back(c);
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
			// for (Component *c : comps)
			// {
			// 	Component *newC = c->perform(event);
			// 	if (newC != NULL)
			// 	{
			// 		add(newC);
			// 	}

			// 	for (Component *c2 : comps)
			// 	{
			// 		if (c != c2 && Collision::canCollide(c, c2))
			// 		{
			// 			c->takeDamage();
			// 			c2->takeDamage();
			// 		}
			// 	}

			// 	if (c->isKilled())
			// 	{
			// 		remove(c);
			// 	}
			// 	}

			loadPendingComponents();
			removeComponents();
			enemySpawner();

			int success = SDL_SetRenderDrawColor(sys.get_ren(), 255, 255, 255, 255);
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

	void Session::removeComponents()
	{
		for (Component *c : toBeRemoved)
		{
			for (std::vector<Component *>::iterator i = comps.begin(); i != comps.end();)
			{
				if (*i == c)
				{
					delete c;
					i = comps.erase(i);
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
		for (Component *c : comps) {
			remove(c);
		}
		removeComponents();
		Background *bg = Background::getInstance(1600, 720, "game_over.jpg");
		add(bg);
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
				}
			}

			if (c->isKilled())
			{
				remove(c);
				if(c->getName() == "Protagonist"){
					gameOver();
					break;
				}
			}
		}
	}

	void Session::enemySpawner()
	{
	
		spawnCounter++;
		if (spawnCounter > howOftenSpawn)
		{
			spawnCounter = 0;
			int amountOfEnemies = enemies.size();

			currentEnemy++;

			if (currentEnemy == amountOfEnemies/3){
				howOftenSpawn = (howOftenSpawn/3)*2;
			}
			if (currentEnemy == (amountOfEnemies/3)*2){
				howOftenSpawn = (howOftenSpawn/3)*2;
			}
			
			if (amountOfEnemies == currentEnemy)
			{
				//currentEnemy = 0; win state?
			}

			add(enemies.at(currentEnemy));
		}
	}	
}