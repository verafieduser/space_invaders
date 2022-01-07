#ifndef ACTOR_H
#define ACTOR_H

#include "Component.h"
#include <SDL2/SDL_image.h>

namespace space_invaders
{
	class Actor : public Component
	{
	public:
		void removal() { this->~Actor(); };
		~Actor();

	protected:
		Actor(int x, int y, int w, int h, std::string images_path);
		Actor(const Actor &sprite) = delete;
		const Actor &operator=(const Actor &) = delete;
		virtual void takeDamage();
		enum Direction
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

		const bool isOutOfBounds() const;
		const bool isOutOfBoundsRight() const;
		const bool isOutOfBoundsLeft() const;
		const bool isMovementAllowed(Direction dir) const;
		
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void kill();
		
		void damageCalculation(std::vector<space_invaders::Component *> comps);
		void collisionConsequences(const std::vector<Component *> &c);
		short int health;
		int speed;
	};
}

extern std::string IMAGES_PATH;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#endif