#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"
#include "System.h"
#include <SDL2/SDL_image.h>
#include <iostream>

namespace space_invaders
{
	class Sprite : public Component
	{
	public:
		enum Direction
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		static Sprite *getInstance(int x, int y, int w, int h, std::string image_path);

		const bool isOutOfBounds() const;
		const bool isOutOfBoundsRight() const;
		const bool isOutOfBoundsLeft() const;
		const bool isMovementAllowed(Direction dir) const;
		void kill();
		void damageCalculation(std::vector<space_invaders::Component *> comps);
		void takeDamage()
		{
			// std::cout << name;
			// if (name == "Protagonist")
			// {
			// 	return;
			// }
			health--;
			if (health <= 0)
			{
				kill();
			}
		};
		void collisionConsequences(std::vector<Component *> &c);
		void removal() { this->~Sprite(); };

		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		Component *perform(std::vector<Component *> &comps);
		void draw() const;
		~Sprite();

	protected:
		Sprite(int x, int y, int w, int h, std::string images_path);
		Sprite(const Sprite &sprite) = delete;
		const Sprite &operator=(const Sprite &) = delete;
		SDL_Texture *sprite;
		short int health;
		int speed = 20;
	};
}

extern std::string IMAGES_PATH;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#endif