#include "Component.h"

namespace space_invaders
{

	Component::Component(int x, int y, int w, int h) : rect{x, y, w, h}
	{
	}

	Component::~Component()
	{
	}
}