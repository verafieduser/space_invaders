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
		//HÄR kraschar den!!!! p.g.a. .get_font ger 0, p.g.a. fonten har en dålig path
		SDL_Surface *surf = TTF_RenderText_Solid(sys.get_font(), text.c_str(), {0, 0, 0});

		texture = SDL_CreateTextureFromSurface(sys.get_ren(), surf);
		SDL_FreeSurface(surf);
	}

	Component* Label::perform(SDL_Event event)
	{
		return NULL;
	}

	void Label::draw() const
	{
		SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
	}

	Label::~Label()
	{
		SDL_DestroyTexture(texture);
	}

	string Label::getText() const
	{
		return text;
	}
	void Label::setText(std::string newText)
	{
		text = newText;
		SDL_DestroyTexture(texture);
		SDL_Surface *surf = TTF_RenderText_Solid(sys.get_font(),
												 text.c_str(), {0, 0, 0});
		texture = SDL_CreateTextureFromSurface(sys.get_ren(), surf);
		SDL_FreeSurface(surf);
	}
}