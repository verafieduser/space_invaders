#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include "Controller.h"

namespace cwing
{

	class System
	{
	public:
		System();
		~System();
		SDL_Renderer *get_ren() const;
		TTF_Font *get_font() const;
		Controller& get_controller() { return controller; };
		void addBackgroundMusic(std::string music_path);

	private:
		SDL_Window *win;
		SDL_Renderer *ren;
		TTF_Font *font;
		Mix_Chunk *music_player;
		Controller controller;
	};

	extern System sys;
}

// extern std::string fontsPath;
// extern std::string imagesPath;
// extern std::string soundsPath;

#endif