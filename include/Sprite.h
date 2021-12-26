#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <string>

namespace cwing
{
	class Sprite : public Component
	{
	public:
		static Sprite *getInstance(int x, int y, int w, int h, std::string image_path);
		int SPEED = 5;
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void perform(SDL_Event event);
		void draw() const;
		virtual void perform(Sprite *source) {}
		~Sprite();

	protected:
		Sprite(int x, int y, int w, int h, std::string images_path);

	private:
		SDL_Texture *texture;
		SDL_Texture *sprite;
	};
}

extern std::string IMAGES_PATH;

#endif