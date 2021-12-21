#include <iostream>
#include "System.h"
#include <SDL2/SDL.h>
#include <iostream>

std::string FONTS_PATH = "./fonts/";
int SCREEN_WIDTH = 1600;
int SCREEN_HEIGHT = 720;
namespace cwing
{

	System::System()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED,
							   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
		TTF_Init();
		// std::cout << " " << fontsPath << " : font path";
		font = TTF_OpenFont((FONTS_PATH + "origintech.ttf").c_str(), 36);
	}

	System::~System()
	{
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
}
