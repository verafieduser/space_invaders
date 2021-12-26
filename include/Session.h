#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <vector>
#include "Component.h"


namespace cwing
{

	class Session
	{
	public:
		void add(Component *c);
		void run();
		~Session();

	private:
		std::vector<Component *> comps;
	};

}

extern std::string IMAGES_PATH;
extern std::string SOUNDS_PATH;
#endif