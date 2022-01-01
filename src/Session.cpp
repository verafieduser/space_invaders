#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Background.h"
#include "Collision.h"
#include "Session.h"
#include "System.h"
#include "Label.h"

int spawnFrequency = 60;
int currentEnemy = 0;
int enemiesDefeated = 0;

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

	void Session::addGameOverComps(Component *c){
		gameOverComps.push_back(c);
	}

	void Session::remove(Component *c)
	{
		toBeRemoved.push_back(c);
	}

	void Session::run()
	{
		std::random_shuffle(enemies.begin(), enemies.end());

		add(scoreLabel);
		add(levelLabel);
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
			removeComponents();
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
		for (Component *c : gameOverComps){
			add(c);
		}
		std::ostringstream ostr;
		ostr << enemiesDefeated;
		scoreLabel->setText("FINAL SCORE: " + ostr.str());
		int middleX = (SCREEN_WIDTH-scoreLabel->getW())/2+150;
		int middleY = SCREEN_HEIGHT/2;
		scoreLabel->setX(middleX);
		scoreLabel->setY(middleY);
		if(!spawningToContinueAfterDeath){
			enemies.clear();
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
				}
			}

			if (c->isKilled())
			{
				remove(c);
				if(c->getName() == "Defeated enemy"){
					std::ostringstream ostr;
					enemiesDefeated++;
					ostr << enemiesDefeated;
					scoreLabel->setText("SCORE: " + ostr.str());
				} else if(c->getName() == "Protagonist"){
					gameOver();
					break;
				}
			}
		}
	}

	void Session::enemySpawner()
	{
	
		spawnCounter++;
		if (spawnCounter > spawnFrequency)
		{
			spawnCounter = 0;
			int amountOfEnemies = enemies.size();

			currentEnemy++;

			//level2 when a third of enemies are defeated
			if (currentEnemy == amountOfEnemies/3){
				spawnFrequency = spawnFrequency / levelDifficultyIncrease;
				levelLabel->setText("Level 2");
				spawnCounter = betweenLevels * 1;
			} 
			// level3 when two thirds of enemies are defeated
			else if (currentEnemy == (amountOfEnemies/3)*2){
				spawnFrequency = spawnFrequency / levelDifficultyIncrease;
				levelLabel->setText("Level 3");
				spawnCounter = betweenLevels * 1;
			}

			if (amountOfEnemies == currentEnemy)
			{
				//currentEnemy = 0; win state?
			}

			add(enemies.at(currentEnemy));
		}
	}	
}