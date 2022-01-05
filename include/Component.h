#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

namespace space_invaders
{
	class Component
	{
	public:
		virtual ~Component();
		virtual void draw() const = 0;
		virtual void removal() = 0;
		virtual void kill() = 0;
		virtual Component *perform(std::vector<Component *>& c) = 0;

		//virtual void tick() = 0;
		const bool isKilled() const { return killed; };
		const bool isCollidable() const { return collidable; };
		const SDL_Rect &getRect() const { return rect; }
		void setY(int &value) { rect.y += value; };
		void setX(int &value) { rect.x += value; };
		void setW(int &value) { rect.w += value; };
		void setH(int &value) { rect.h += value; };
		const int getY() const { return rect.y; };
		const int getX() const { return rect.x; };
		const int getW() const { return rect.w; };
		const int getH() const { return rect.h; };
		const std::string getName() const { return name; }; // const int getY() const {return rect.y;};
															// const int getX() const {return rect.x;};
		const bool canCollideWith(const Component *c) const;


	protected:
		Component(int x, int y, int w, int h);
		bool killed = false;
		bool collidable;
		std::string name;

	private:
		SDL_Rect rect;
		Component(const Component &) = delete;
		const Component &operator=(const Component &) = delete;
	};
}
#endif
