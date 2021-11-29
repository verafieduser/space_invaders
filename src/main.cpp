#include <SDL2/SDL.h>
#include "Label.h"
#include "Session.h"
#include "Button.h"
#include <string>
#include <iostream>

// Paths to resource folders. Change to your own path!
std::string resPath = "./resources/";
std::string imagesPath = "./images/";
std::string fontsPath = "./fonts/";
std::string soundsPath = "./sounds/";

using namespace std;
using namespace cwing;

int value = 0;

class OkaKnapp : public Button {
public:
	OkaKnapp(Label *lbl) :Button(100, 100, 150, 70, "Oka"), label(lbl) {}
	void perform(Button* source) {
		value++;
		label->setText(to_string(value));
	}
private:
	Label* label;
};


class MinskaKnapp : public Button {
public:
	MinskaKnapp(Label *lbl) :Button(400, 100, 150, 70, "Minska"), label(lbl) {}
	void perform(Button* source) {
		value--;
		label->setText(to_string(value));
	}
private:
	Label* label;
};


int main(int argc, char** argv) {
	Session ses;
	// Backgroud* bg = Background::;
	// ses.add(bg);	

	Label* lbl = Label::getInstance(270, 100, 100, 70, "0");

	ses.add(lbl);
	Button* b = new OkaKnapp(lbl);
	ses.add(b);
	Button* b2 = new MinskaKnapp(lbl);
	ses.add(b2);
	ses.run();

	return 0;
}




// #include <iostream>
// #include <string>

// // Alla dessa SDL inkluderingsfiler används inte i detta testprogram.
// // Bifogas endast för test av SDL installation!

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_ttf.h>

// //#define FPS 60

// int main(int argc, char *argv[])
// {

// 	// Paths to resources
// 	//std::string imagePath = "../../images/";
// 	std::string imagePath = "./images/";

// 	//std::string fontPath = "../../fonts/";
// 	std::string fontPath = "./fonts/";

// 	//std::string soundPath = "../../sounds/";
// 	std::string soundPath = "./sounds/";

// 	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
// 	{
// 		std::cout << "Error SDL2 Initialization : " << SDL_GetError();
// 		return EXIT_FAILURE;
// 	}

// 	if (TTF_Init() < 0)
// 	{
// 		std::cout << "Error SDL_ttf Initialization : " << SDL_GetError();
// 		return EXIT_FAILURE;
// 	}

// 	SDL_Window *window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 720, 0);
// 	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

// 	std::cout << (imagePath + "bg.jpg").c_str() << std::endl;

// 	SDL_Surface *bg_sur = IMG_Load((imagePath + "bg.png").c_str());

// 	SDL_Texture *bg_tex = SDL_CreateTextureFromSurface(renderer, bg_sur);
// 	SDL_FreeSurface(bg_sur);

// 	std::cout << "Avsluta programmet genom \"quit\" från fönstrets meny eller genom att stänga fönstret!" << std::endl;

// 	//The background scrolling offset
// 	// int scrollingOffset = 0;

// 	// Loop till dess att programmet avslutas!
// 	bool running = true;
// 	while (running)
// 	{
// 		SDL_Event e;
// 		if (SDL_PollEvent(&e))
// 		{
// 			if (e.type == SDL_QUIT)
// 			{
// 				running = false;
// 			}
// 		}

// 		SDL_RenderClear(renderer);
// 		SDL_RenderCopy(renderer, bg_tex, NULL, NULL);
// 		SDL_RenderPresent(renderer);
// 	}

// 	// Städa innan programmet avslutas!

// 	SDL_DestroyTexture(bg_tex);
// 	SDL_DestroyRenderer(renderer);
// 	SDL_DestroyWindow(window);

// 	TTF_Quit();
// 	SDL_Quit();

// 	return EXIT_SUCCESS;
// }