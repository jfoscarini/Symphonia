#ifndef SYMPHONIA_GAME_H
#define SYMPHONIA_GAME_H

#include <memory>
#include <vector>
#include <deque>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "Screen.h"

namespace sym {

    class Game {
    public:
        Game();
        ~Game();

        void run();

        static std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
        static std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;

        static std::deque<std::unique_ptr<Screen>> new_screens;

    private:
        bool isRunning();
        void populateScreens();

        std::vector<std::unique_ptr<Screen>> screens;

        Uint32 sdl_flags = SDL_INIT_EVERYTHING;
        int mix_flags = MIX_INIT_MP3;

        Uint32 window_flags = SDL_WINDOW_RESIZABLE
                | SDL_WINDOW_ALLOW_HIGHDPI;

        Uint32 renderer_flags = SDL_RENDERER_ACCELERATED
                | SDL_RENDERER_PRESENTVSYNC
                | SDL_RENDERER_TARGETTEXTURE;

        const char* window_title = "Symhponia";
        const int minimum_width = 640, window_width = 640;
        const int minimum_height = 480, window_height = 480;
    };

}

#endif //SYMPHONIA_GAME_H
