#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL2/SDL.h>
#include <iostream>

namespace space_invaders
{
    class Controller
    {
    public:
        static Controller *getInstance(){return new Controller(); };
        const Uint8 *getKeyboardState() const { return SDL_GetKeyboardState(NULL); };
        const Uint32 getMouseState() const { return SDL_GetMouseState(NULL, NULL); };
    private:
        Controller(){};
        const Controller &operator=(const Controller &) = delete;
		Controller(const Controller &) = delete;
    };
}

#endif