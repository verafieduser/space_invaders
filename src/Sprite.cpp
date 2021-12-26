#include "Sprite.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <SDL2/SDL_image.h>

namespace cwing
{

	Sprite::Sprite(int x, int y, int w, int h, std::string image_path, Session &s) : Component(x, y, w, h)
	{
		sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
		session = s;
	}

	Sprite::~Sprite()
	{
		SDL_DestroyTexture(texture);
		SDL_DestroyTexture(sprite);
	}

	Sprite *Sprite::getInstance(int x, int y, int w, int h, std::string image_path, Session &s)
	{
		return new Sprite(x, y, w, h, image_path, s);
	}

	const bool Sprite::isOutOfBounds()
	{
		bool outOfBounds = false;
		if (getY() < 0 || getY() > SCREEN_HEIGHT - getH() || getX() < 0 || getX() > SCREEN_WIDTH - getW())
		{
			outOfBounds = true;
		}
		return outOfBounds;
	}

	const bool Sprite::isOutOfBoundsLeft()
	{
		bool outOfBounds = false;
		if (getX() < 0)
		{
			outOfBounds = true;
		}
		return outOfBounds;
	}

	const bool Sprite::isOutOfBoundsRight()
	{
		bool outOfBounds = false;
		if (getX() > SCREEN_WIDTH - getW())
		{
			outOfBounds = true;
		}
		return outOfBounds;
	}

	const bool Sprite::isMovementAllowed(Direction dir)
	{
		switch (dir)
		{
		case RIGHT:
			if (getX() < SCREEN_WIDTH - getW())
			{
				return true;
			}
			break;
		case LEFT:
			if (getX() > 0)
			{
				return true;
			}
			break;
		case DOWN:
			if (getY() < SCREEN_HEIGHT - getH())
			{
				return true;
			}
			break;
		case UP:
			if (getY() > 0)
			{
				return true;
			}
			break;

		default:
			break;
		}

		return false;
	}




	void Sprite::moveUp()
	{
		if (isMovementAllowed(UP))
		{
			int value = -1 * SPEED;
			setY(value);
		}
	}

	void Sprite::moveDown()
	{
		if (isMovementAllowed(DOWN))
		{
			setY(SPEED);
		}
	}

	void Sprite::moveLeft()
	{
		if (isMovementAllowed(LEFT))
		{
			int value = -1 * SPEED;
			setX(value);
		}
	}

	void Sprite::moveRight()
	{
		if (isMovementAllowed(RIGHT))
		{
			setX(SPEED);
		}
	}

	void Sprite::kill()
	{
		killed = true;
	}

	void Sprite::perform(SDL_Event event)
	{
		//implement this
		// switch (event.key.keysym.sym)
		// {
		// case SDLK_RIGHT:
		// 	moveUp();
		// 	break;
		// case SDLK_LEFT:
		// 	moveDown();
		// 	break;
		// case SDLK_UP:
		// 	moveLeft();
		// 	break;
		// case SDLK_DOWN:
		// 	moveRight();
		// 	break;
		// }
	}

	void Sprite::draw() const
	{

		SDL_RenderCopy(sys.get_ren(), sprite, NULL, &getRect());

		SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
	}
}