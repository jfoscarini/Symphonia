#ifndef SYMPHONIA_GAME_H
#define SYMPHONIA_GAME_H

#include <memory>
#include <vector>
#include <deque>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Screen.h"

namespace sym {

    class Game {
    public:
        Game();
        ~Game();

        void run();

        static SDL_Point getRelativeMousePosition(int x, int y);

        static std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
        static std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;

        template <typename T, typename... Args>
        [[maybe_unused]] static T load(
                [[maybe_unused]] const std::string &name,
                [[maybe_unused]] const std::string &path,
                [[maybe_unused]] Args... args);
        template <typename T>
        [[maybe_unused]] static T get([[maybe_unused]] const std::string &name);
        template <typename T>
        [[maybe_unused]] static T put([[maybe_unused]] const std::string &name, [[maybe_unused]] T what);
        template <typename T>
        [[maybe_unused]] static void free([[maybe_unused]] const std::string &name);

        static std::deque<std::unique_ptr<Screen>> new_screens;

    private:
        bool isRunning();
        void populateScreens();

        void handleEvents(SDL_Event &event) const;

        std::vector<std::unique_ptr<Screen>> screens;

        static std::unordered_map<std::string, std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>> fonts;
        static std::unordered_map<std::string, std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>> textures;

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
        static std::pair<float, float> pixel_per_pixel;
    };

}

#endif //SYMPHONIA_GAME_H
