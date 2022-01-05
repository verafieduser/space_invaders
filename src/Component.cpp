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

	// const bool Component::canCollideWith(const Component *c) const {

	// 	std::string name2 = c->getName();

	//     if (name == "Protagonist" && name2 == "Enemy bullet")
	//     {
	//         if (Collision::AABB(getRect(), c->getRect()))
	//         {
	//             return true;
	//         }
	//     }

	//     if (name == "Protagonist bullet" && name2 == "Enemy")
	//     {
	//         if (Collision::AABB(getRect(), c->getRect()))
	//         {
	//             return true;
	//         }
	//     }

	//     if ((name == "Protagonist bullet" || name == "Enemy bullet") && name2 == "Debris")
	//     {
	//         if (Collision::AABB(getRect(), c->getRect()))
	//         {

	//             return true;
	//         }
	//     }

	//     if (name == "Protagonist" && name2 == "Debris")
	//     {
	//         if (Collision::AABB(c->getRect(), c->getRect()))
	//         {

	//             return true;
	//         }
	//     }

	//     if (name == "Protagonist" && name2 == "Enemy")
	//     {
	//         if (Collision::AABB(getRect(), c->getRect()))
	//         {

	//             return true;
	//         }
	//     }

	//     if (name == "Protagonist bullet" && name2 == "Enemy bullet")
	//     {
	//         if (Collision::AABB(getRect(), c->getRect()))
	//         {

	//             return true;
	//         }
	//     }

	//     return false;
	// }

}