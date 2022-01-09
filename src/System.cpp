#include <iostream>
#include "System.h"

std::string IMAGES_PATH = "./images/";
std::string SOUNDS_PATH = "./sounds/";
std::string FONTS_PATH = "./fonts/";
int SCREEN_WIDTH = 1600;
int SCREEN_HEIGHT = 720;

namespace space_invaders
{
	System::System()
	{

		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED,
							   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

		if (win == NULL)
		{
			std::cout << SDL_GetError();
		}

		ren = SDL_CreateRenderer(win, -1, 0);

		if (ren == NULL)
		{
			std::cout << SDL_GetError();
		}

		int success = TTF_Init() + 1;
		if (!success)
		{
			std::cout << SDL_GetError() << " TTF_INIT Error\n";
		}
		font = TTF_OpenFont((FONTS_PATH + "origintech.ttf").c_str(), 38);
	}

	System::~System()
	{
		controller->~Controller();
		if(music_player != NULL){
			Mix_Quit();
		}
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		SDL_Quit();
	}

	SDL_Renderer *System::get_ren() const
	{
		return ren;
	}

	TTF_Font *System::get_font() const
	{
		return font;
	}
	System sys;

	void System::addBackgroundMusic(std::string music_path)
	{
		Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
		music_player = Mix_LoadWAV(music_path.c_str());
		Mix_PlayChannel(-1, music_player, -1);
	}
}
