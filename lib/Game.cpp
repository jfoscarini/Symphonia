#include <stdexcept>
#include <string>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Game.h"

std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> sym::Game::window(nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> sym::Game::renderer(nullptr, SDL_DestroyRenderer);

std::deque<std::unique_ptr<sym::Screen>> sym::Game::new_screens;

sym::Game::Game() {
    if (SDL_Init(sdl_flags) != 0)
        throw std::runtime_error("Could not initialize SDL: " + std::string(SDL_GetError()));

    if (TTF_Init() != 0)
        throw std::runtime_error("Could not initialize TTF: " + std::string(TTF_GetError()));

    if (Mix_Init(mix_flags) == 0)
        throw std::runtime_error("Could not initialize MIX: " + std::string(Mix_GetError()));

    auto new_window = SDL_CreateWindow(
            window_title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            window_width,
            window_height,
            window_flags
    );
    if (!new_window)
        throw std::runtime_error("Could not create window: " + std::string(SDL_GetError()));

    SDL_SetWindowMinimumSize(new_window, minimum_width, minimum_height);

    auto new_renderer = SDL_CreateRenderer(new_window, -1, renderer_flags);
    if (!new_renderer)
        throw std::runtime_error("Could not create renderer: " + std::string(SDL_GetError()));

    window.reset(new_window);
    renderer.reset(new_renderer);
}

sym::Game::~Game() {
    screens.clear();
    new_screens.clear();

    renderer.reset();
    window.reset();

    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void sym::Game::run() {
    Screen *screen;
    SDL_Event event;

    populateScreens();

    while(isRunning()) {
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer.get());

        screen = screens.back().get();

        while (SDL_PollEvent(&event)) screen->input(event);
        screen->update();
        screen->draw();

        if (!screen->alive()) screens.pop_back();
        if (!new_screens.empty()) populateScreens();

        SDL_RenderPresent(renderer.get());
    }
}

bool sym::Game::isRunning() {
    SDL_PumpEvents();
    return SDL_PeepEvents(nullptr, 1, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) == 0 && !screens.empty();
}

void sym::Game::populateScreens() {
    std::erase_if(new_screens, [](const auto& screen) { return !screen; });
    while(!new_screens.empty()) {
        screens.push_back(std::move(new_screens.front()));
        new_screens.pop_front();
    }
}
