#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>
#include <string>

namespace cwing
{
	class Component
	{
	public:
		virtual ~Component();
		virtual void draw() const = 0;
		virtual void removal() = 0;
		virtual void kill() = 0;
		virtual Component *perform(SDL_Event event) = 0;
		virtual void takeDamage() = 0;

		//virtual void tick() = 0;
		const bool isKilled() const { return killed; };
		const bool isCollidable() const { return collidable; };
		const SDL_Rect &getRect() const { return rect; }
		void setY(int &value) { rect.y += value; };
		void setX(int &value) { rect.x += value; };
		void setW(int &value) { rect.w += value; };
		void setH(int &value) { rect.h += value; };
		const int getY() { return rect.y; };
		const int getX() { return rect.x; };
		const int getW() { return rect.w; };
		const int getH() { return rect.h; };
		const std::string getName() const {return name;};		// const int getY() const {return rect.y;};
		// const int getX() const {return rect.x;};

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
