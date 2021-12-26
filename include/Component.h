#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>

namespace cwing
{
	class Component
	{
	public:
		virtual ~Component();
		virtual void spaceDown(const SDL_Event &) {}
		virtual void mouseDown(const SDL_Event &) {}
		virtual void mouseUp(const SDL_Event &) {}
		virtual void keyDown(const SDL_Event &) {}
		virtual void keyUp(const SDL_Event &) {}
		virtual void draw() const = 0;
		virtual void perform(SDL_Event event) = 0;
		//virtual void tick() = 0;
		const bool isKilled() const { return killed; };
		const SDL_Rect &getRect() const { return rect; }
		void setY(int &value) { rect.y += value; };
		void setX(int &value) { rect.x += value; };
		const int getY() { return rect.y; };
		const int getX() { return rect.x; };
		const int getW() { return rect.w; };
		const int getH() { return rect.h; };
		// const int getY() const {return rect.y;};
		// const int getX() const {return rect.x;};

	protected:
		Component(int x, int y, int w, int h);
		bool killed = false;

	private:
		SDL_Rect rect;
		Component(const Component &) = delete;
		const Component &operator=(const Component &) = delete;
	};
}
#endif
