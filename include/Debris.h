#include "Sprite.h"
#include "Session.h"
#include <SDL2/SDL.h>

namespace cwing
{

    class Debris : public Sprite
    {
    public:
        static Debris *getInstance(int x, int y, int w, int h, std::string image_path, Session &session, int speed);

        // void moveUp();
        // void moveDown();
        void moveLeft();
        // void moveRight();
        void spinDebris(const int &speed);
        void setAngle(const int &angle);
        void draw() const;
        Component* perform(SDL_Event event);
        ~Debris();

    protected:
        Debris(int x, int y, int w, int h, std::string images_path, Session &session, int speed);

    private:
        float angle = 0;
        SDL_Texture *texture;
        SDL_Texture *sprite;
    };
}
extern std::string IMAGES_PATH;
