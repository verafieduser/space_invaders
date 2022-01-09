#include "Actor.h"
#include "Collision.h"

namespace space_invaders
{

	Actor::Actor(int x, int y, int w, int h, std::string image_path) : Component(x, y, w, h)
	{
		sprite = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
		collidable = true;
	}

	// Actor *Actor::getInstance(int x, int y, int w, int h, std::string image_path)
	// {
	// 	return new Actor(x, y, w, h, image_path);
	// }

	Actor::~Actor()
	{
		SDL_DestroyTexture(sprite);
	}

	const bool Actor::isOutOfBounds() const
	{
		if (getY() < 0 || getY() > SCREEN_HEIGHT - getH() || getX() < 0 || getX() > SCREEN_WIDTH - getW())
		{
			return true;
		}
		return false;
	}

	const bool Actor::isOutOfBoundsRight() const
	{
		if (getX() - getW() > SCREEN_WIDTH - getW())
		{
			return true;
		}
		return false;
	}

	const bool Actor::isOutOfBoundsLeft() const
	{
		if (getX() + getW() < 0)
		{
			return true;
		}
		return false;
	}

	const bool Actor::isMovementAllowed(Direction dir) const
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

	void Actor::takeDamage()
	{
		health--;
		if (health <= 0)
		{
			kill();
		}
	};

	void Actor::moveUp()
	{
		if (isMovementAllowed(UP))
		{
			int value = -1 * speed;
			setY(value);
		}
	}

	void Actor::moveDown()
	{
		if (isMovementAllowed(DOWN))
		{
			setY(speed);
		}
	}

	void Actor::moveLeft()
	{
		if (isMovementAllowed(LEFT))
		{
			int value = -1 * speed;
			setX(value);
		}
	}

	void Actor::moveRight()
	{
		if (isMovementAllowed(RIGHT))
		{
			setX(speed);
		}
	}

	void Actor::kill()
	{
		killed = true;
	}

	void Actor::collisionConsequences(const std::vector<Component *> &comps)
	{
		for (Component *c : comps)
		{
			if (this != c && Collision::canCollideWith(this, c))
			{
				this->takeDamage();
				Actor *sprite = dynamic_cast<Actor *>(c);
				if (sprite != NULL)
				{
					sprite->takeDamage();
				}
			}
		}
	}
}