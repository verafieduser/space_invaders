#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Component.h"

namespace space_invaders
{
    class Healthbar : public Component
    {
    public:
        static Healthbar *getInstance(int x, int y, int w, int h, std::string full_health_image_path, std::string half_health_image_path, std::string low_health_image_path);
        ~Healthbar();
        Component *perform(const std::vector<Component *>& comps) { return NULL; };
        void removal() { this->~Healthbar(); };
        void updateHealth(int i);

    protected:
        Healthbar(int x, int y, int w, int h, std::string full_health_image_path, std::string half_health_image_path, std::string low_health_image_path);

    private:
        Healthbar(const Healthbar &healthbar) = delete;
        const Healthbar &operator=(const Healthbar&) = delete;
        void setTexture(std::string image_path);
        void updateTexture();
        short int health;
        std::string full_health_image_path, half_health_image_path, low_health_image_path;
    };
}
extern std::string IMAGES_PATH;

#endif
