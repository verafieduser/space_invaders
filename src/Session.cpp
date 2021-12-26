#include "Session.h"
#include <SDL2/SDL.h>
#include "System.h"

namespace cwing
{

	void Session::add(Component *c)
	{
		comps.push_back(c);
	}

	void Session::run()
	{
		bool quit = false;
		while (!quit)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					for (Component *c : comps)
						c->mouseDown(event);
					break;
				case SDL_MOUSEBUTTONUP:
					for (Component *c : comps)
						c->mouseUp(event);
					break;
				case SDL_KEYDOWN:
					for (Component *c : comps)
					{

						c->perform(event);
						//TODO: move this switch into a "perform()" or something inside component - and then override in relevant subclasses.

						/*if (instanceof <Sprite>(c))
						{
							switch (event.key.keysym.sym)
							{
							case SDLK_RIGHT:
								c->moveUp();
								break;
							case SDLK_LEFT:
								c->moveDown();
								break;
							case SDLK_UP:
								c->moveLeft();
								break;
							case SDLK_DOWN:
								c->moveRight();
								break;
							}
						}
						*/
					}
					break;
				case SDL_KEYUP:
					for (Component *c : comps)
						c->keyUp(event);
					break;

				} // switch
			}	  // inre while
			SDL_SetRenderDrawColor(sys.get_ren(), 255, 255, 255, 255);
			SDL_RenderClear(sys.get_ren());
			for (Component *c : comps)
				c->draw();
			SDL_RenderPresent(sys.get_ren());

		} //yttre while
	}

	Session::~Session()
	{
	}
}