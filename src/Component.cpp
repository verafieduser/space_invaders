#include "Component.h"
#include "Collision.h"

namespace space_invaders
{

	Component::Component(int x, int y, int w, int h) : rect{x, y, w, h}
	{
	}

	Component::~Component()
	{
	}

	Component *Component::perform(const std::vector<Component *> &comps)
	{
		return NULL;
	}

	void Component::draw() const
	{
		int success = SDL_RenderCopy(sys.get_ren(), sprite, NULL, &getRect()) + 1;
		if (!success)
		{
			std::cout << SDL_GetError() << " in RenderCopy sprite in Actor \n"
					  << " file was " << name + "\n";
		}	
	}

	void Component::kill()
	{
		killed = true;
	}
}