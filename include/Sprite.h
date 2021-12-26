#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"
#include "Session.h"
#include <SDL2/SDL.h>
#include <string>

namespace cwing
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
		static Sprite *getInstance(int x, int y, int w, int h, std::string image_path, Session &session);
		int SPEED = 20;
		const bool isOutOfBounds();
		const bool isOutOfBoundsRight();
		const bool isOutOfBoundsLeft();
		const bool isMovementAllowed(Direction dir);
		void kill();

		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void perform(SDL_Event event);
		void draw() const;
		~Sprite();



	protected:
		Sprite(int x, int y, int w, int h, std::string images_path, Session &session);
		Session session;

	private:
		SDL_Texture *texture;
		SDL_Texture *sprite;
	};
}

extern std::string IMAGES_PATH;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#endif