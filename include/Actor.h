#ifndef ACTOR_H
#define ACTOR_H

#include "Component.h"
#include "System.h"
#include <SDL2/SDL_image.h>
#include <iostream>

namespace space_invaders
{
	class Actor : public Component
	{
	public:
		enum Direction
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		static Actor *getInstance(int x, int y, int w, int h, std::string image_path);

		const bool isOutOfBounds() const;
		const bool isOutOfBoundsRight() const;
		const bool isOutOfBoundsLeft() const;
		const bool isMovementAllowed(Direction dir) const;
		void kill();
		void damageCalculation(std::vector<space_invaders::Component *> comps);
		virtual void takeDamage()
		{
			health--;
			if (health <= 0)
			{
				kill();
			}
		};
		void collisionConsequences(const std::vector<Component *> &c);
		void removal() { this->~Actor(); };

		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		Component *perform(const std::vector<Component *> &comps);
		void draw() const;
		~Actor();

	protected:
		Actor(int x, int y, int w, int h, std::string images_path);
		Actor(const Actor &sprite) = delete;
		const Actor &operator=(const Actor &) = delete;
		SDL_Texture *sprite;
		short int health;
		int speed;
	};
}

extern std::string IMAGES_PATH;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#endif