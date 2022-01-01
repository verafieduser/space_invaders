#include "Healthbar.h"
#include <iostream>
#include "System.h"
#include <SDL2/SDL_image.h>
#include <string>

namespace cwing
{
    Healthbar::Healthbar(int x, int y, int w, int h, std::string full_health_path, std::string half_health_path, std::string low_health_path) : Component(x, y, w, h) {
        full_health_image_path = full_health_path;
        half_health_image_path = half_health_path;
        low_health_image_path = low_health_path;
        health = 3;
        name = "Healthbar";
        updateTexture();
        collidable = false;
    }
    
    Healthbar *Healthbar::getInstance(int x, int y, int w, int h, std::string full_health_path,  std::string half_health_path, std::string low_health_path)
	{
		return new Healthbar(x, y, w, h, full_health_path, half_health_path, low_health_path);
	}

    Healthbar::~Healthbar()
	{
		SDL_DestroyTexture(texture);
	}

    void Healthbar::updateTexture() {
        switch (health)
        {
        case 3:
            setTexture(full_health_image_path);
            break;
        case 2:
            setTexture(half_health_image_path);
            break;
        case 1:
            setTexture(low_health_image_path);
            break;
        default:
            break;
        }
    }

    void Healthbar::setTexture(std::string image_path) 
    {
        // std:: cout << "set texture reached, before if" << std::endl;
        //TODO: should we destroy old texture here?
        //SDL_DestroyTexture(texture);
        // std:: cout << "set texture reached, after if" << std::endl;
        texture = IMG_LoadTexture(sys.get_ren(), (IMAGES_PATH + image_path).c_str());
        // std:: cout << "set texture reached, after loading" << std::endl;
    }

    void Healthbar::updateHealth(int i) 
    {
        health += i;
        updateTexture();
    }

    void Healthbar::draw() const 
    {
        int success = SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect()) + 1;
        if (!success)
        {
            std::cout << SDL_GetError() << " in RenderCopy sprite in Healthbar \n"
                      << " file was " << name + "\n";
        }
    }
}
