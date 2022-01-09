#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Controller.h"
#include <string>

namespace space_invaders
{

	class System
	{
	public:
		System();
		~System();
		SDL_Renderer *get_ren() const;
		TTF_Font *get_font() const;
		const Controller& get_controller() { return *controller; };
		void addBackgroundMusic(std::string music_path);

	private:
		System(const System &system) = delete;
        const System &operator=(const System&) = delete;
		SDL_Window *win;
		SDL_Renderer *ren;
		TTF_Font *font;
		Mix_Chunk *music_player;
		Controller * controller = Controller::getInstance();
	};

	extern System sys;
}

#endif