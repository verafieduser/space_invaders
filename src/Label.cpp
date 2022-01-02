#include "Label.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <iostream>
#include <string>
using namespace std;

namespace cwing
{

	Label *Label::getInstance(int x, int y, int w,
							  int h, std::string txt)
	{

		return new Label(x, y, w, h, txt);
	}

	Label::Label(int x, int y, int w, int h,
				 std::string txt) : Component(x, y, w, h), text(txt)
	{
		color = {200, 0, 255};
		originalColor = {200, 0, 255};
        name = "Label";
        collidable = false;
		SDL_Surface *surf = TTF_RenderText_Solid(sys.get_font(), text.c_str(), color);

		texture = SDL_CreateTextureFromSurface(sys.get_ren(), surf);
		SDL_FreeSurface(surf);

	}


	Label::~Label()
	{
		SDL_DestroyTexture(texture);
	}

	void Label::setText(std::string newText)
	{
		text = newText;
		SDL_DestroyTexture(texture);
		SDL_Surface *surf = TTF_RenderText_Solid(sys.get_font(),
												 text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(sys.get_ren(), surf);
		SDL_FreeSurface(surf);
	}
}