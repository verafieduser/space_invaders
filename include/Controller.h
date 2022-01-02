#ifndef CONTROLLER_H
#define CONTROLLER_H

namespace cwing
{



    class Controller
    {
    public:
        const Uint8* getKeyboardState() const {return SDL_GetKeyboardState(NULL);};
        const Uint32 getMouseState() const {return SDL_GetMouseState(NULL,NULL);};
    };
}

#endif