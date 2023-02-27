#ifndef SYMPHONIA_SCREEN_H
#define SYMPHONIA_SCREEN_H

#include <SDL2/SDL.h>

namespace sym {

    class Screen {
    public:
        virtual ~Screen() = default;

        virtual void input(SDL_Event &event) = 0;
        virtual void update() = 0;
        virtual void draw() = 0;

        virtual bool alive() = 0;
    };

}

#endif //SYMPHONIA_SCREEN_H
