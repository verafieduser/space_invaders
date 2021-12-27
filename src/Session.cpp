#include "Session.h"
#include <SDL2/SDL.h>
#include "System.h"
#include <iostream>
#include <vector>
#include "Collision.h"
#include "Enemy.h"
#include <sstream>

int spawnCounter = 100;
int enemyType = 1;
int typesOfEnemies = 3;

namespace cwing
{
#define FPS 60;

	void Session::add(Component *c)
	{
		comps.push_back(c);
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

			for (Component *c : comps)
			{
				for (Component *c2 : comps)
				{
					if (c != c2 && c->isCollidable() && c2->isCollidable() && Collision::AABB(c->getRect(), c2->getRect()))
					{
						c->kill();
						c2->kill();
					}
				}
				Component *newC = c->perform(event);
				if (newC != NULL)
				{
					add(newC);
				}
				if (c->isKilled())
				{
					for (std::vector<Component *>::iterator i = comps.begin(); i != comps.end();)
						if (*i == c)
						{
							i = comps.erase(i);
						}
						else
							i++;
					c->removal();
				}
			}
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
}