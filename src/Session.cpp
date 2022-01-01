#include <SDL2/SDL.h>
#include <sstream>
#include <iostream>
#include <vector>
#include "Background.h"
#include "Collision.h"
#include "Enemy.h"
#include "Session.h"
#include "System.h"

int spawnCounter = 100;
int enemyType = 1;
int typesOfEnemies = 3;

namespace cwing
{
#define FPS 60;

	void Session::add(Component *c)
	{
		toBeAdded.push_back(c);
	}

	void Session::remove(Component *c)
	{
		toBeRemoved.push_back(c);
	}

	void Session::run()
	{
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
		if (spawnCounter > 100)
		{
			spawnCounter = 0;
			std::ostringstream ostr;
			ostr << enemyType;
			srand(time(NULL));
			Enemy *enemy = Enemy::getInstance(1800, rand() % 500 + 100, 100, 100, "enemy" + ostr.str() + ".png");
			enemyType++;
			if (enemyType > typesOfEnemies)
			{
				enemyType = 1;
			}
			add(enemy);
		}
	}	
}