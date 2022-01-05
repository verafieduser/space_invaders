#include "Sprite.h"
#include "Collision.h"

namespace space_invaders
{

	Sprite::Sprite(int x, int y, int w, int h, std::string image_path) : Component(x, y, w, h)
	{
		sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
		collidable = true;
	}

	Sprite *Sprite::getInstance(int x, int y, int w, int h, std::string image_path)
	{
		return new Sprite(x, y, w, h, image_path);
	}

	Sprite::~Sprite()
	{
		SDL_DestroyTexture(sprite);
	}

	const bool Sprite::isOutOfBounds() const
	{
		if (getY() < 0 || getY() > SCREEN_HEIGHT - getH() || getX() < 0 || getX() > SCREEN_WIDTH - getW())
		{
			return true;
		}
		return false;
	}

	void Sprite::collisionConsequences(std::vector<Component *>& comps)
	{
		for (Component *c : comps)
		{
			if (this != c && Collision::canCollideWith(this, c))
			{
				takeDamage();
				// Sprite *sprite = dynamic_cast<Sprite *> (c);
				// if (sprite != NULL){
				// 	sprite->takeDamage();
				// }

			}
		}
	}



	const bool Sprite::isOutOfBoundsLeft() const
	{
		if (getX() + getW() < 0)
		{
			return true;
		}
		return false;
	}

	const bool Sprite::isOutOfBoundsRight() const
	{
		if (getX() - getW() > SCREEN_WIDTH - getW())
		{
			return true;
		}
		return false;
	}

	const bool Sprite::isMovementAllowed(Direction dir) const
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
			int value = -1 * speed;
			setY(value);
		}
	}

	void Sprite::moveDown()
	{
		if (isMovementAllowed(DOWN))
		{
			setY(speed);
		}
	}

	void Sprite::moveLeft()
	{
		if (isMovementAllowed(LEFT))
		{
			int value = -1 * speed;
			setX(value);
		}
	}

	void Sprite::moveRight()
	{
		if (isMovementAllowed(RIGHT))
		{
			setX(speed);
		}
	}

	void Sprite::kill()
	{
		killed = true;
	}

	Component *Sprite::perform(std::vector<Component *>& comps)
	{
		return NULL;
	}

	void Sprite::draw() const
	{
		int success = SDL_RenderCopy(sys.get_ren(), sprite, NULL, &getRect()) + 1;
		if (!success)
		{
			std::cout << SDL_GetError() << " in RenderCopy sprite in Sprite \n"
					  << " file was " << name + "\n";
		}
	}
}