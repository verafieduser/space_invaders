#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Component.h"
#include <SDL2/SDL.h>

namespace cwing {
	class Background : public Component
	{
	public:
		virtual ~Background();
		virtual void mouseDown(const SDL_Event&) {}
		virtual void mouseUp(const SDL_Event&) {}
		virtual void keyDown(const SDL_Event&) {}
		virtual void keyUp(const SDL_Event&) {}
		virtual void draw() const = 0;
		const SDL_Rect& getRect() const { return rect; }
	protected:
		Background(int x, int y, int w, int h);
	private:
		SDL_Rect rect;
		Background(const Background&) = delete;
		const Background& operator=(const Background&) = delete;
	};
}
#endif
