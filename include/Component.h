#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <iostream>
#include "System.h"


namespace space_invaders
{
	class Component
	{
	public:
		virtual ~Component();

		virtual void removal() = 0;

		virtual Component *perform(const std::vector<Component *>& comps);
		virtual void draw() const;
		virtual void kill();
		
		const SDL_Rect &getRect() const { return rect; }
		const int getY() const { return rect.y; };
		const int getX() const { return rect.x; };
		const int getW() const { return rect.w; };
		const int getH() const { return rect.h; };
		 
		const std::string getName() const { return name; };													
		const bool canCollideWith(const Component *c) const;
		const bool isKilled() const { return killed; };
		const bool isCollidable() const { return collidable; };

		void setY(int &value) { rect.y += value; };
		void setX(int &value) { rect.x += value; };
		void setW(int &value) { rect.w += value; };
		void setH(int &value) { rect.h += value; };

	protected:
		Component(int x, int y, int w, int h);
		std::string name;
		bool collidable;
		bool killed = false;
		SDL_Texture *sprite;

	private:
		const Component &operator=(const Component &) = delete;
		Component(const Component &) = delete;
		SDL_Rect rect;	

	};
}
#endif
