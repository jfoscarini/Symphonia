#include <stdexcept>
#include <string>
#include <algorithm>

#include <SDL2/SDL_image.h>

#include "Game.h"

std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> sym::Game::window(nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> sym::Game::renderer(nullptr, SDL_DestroyRenderer);

std::unordered_map<std::string, std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>> sym::Game::fonts;
std::unordered_map<std::string, std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>> sym::Game::textures;

std::deque<std::unique_ptr<sym::Screen>> sym::Game::new_screens;

std::pair<float, float> sym::Game::pixel_per_pixel;

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

    fonts.clear();

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

        while (SDL_PollEvent(&event)) {
            handleEvents(event);
            screen->input(event);
        }
        screen->update();
        screen->draw();

        if (!screen->alive()) screens.pop_back();
        if (!new_screens.empty()) populateScreens();

        SDL_RenderPresent(renderer.get());
    }
}

SDL_Point sym::Game::getRelativeMousePosition(int x, int y) {
    return {
            static_cast<int>(static_cast<float>(x) * pixel_per_pixel.first),
            static_cast<int>(static_cast<float>(y) * pixel_per_pixel.second)
    };
}

template<typename T, typename... Args>
[[maybe_unused]] T sym::Game::load(
        [[maybe_unused]] const std::string &name,
        [[maybe_unused]] const std::string &path,
        [[maybe_unused]] Args... args) {
    return nullptr;
}

template<>
[[maybe_unused]] SDL_Texture *sym::Game::load(const std::string &name, const std::string &path) {
    auto it = textures.find(name);
    if (it != textures.end()) return it->second.get();

    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface)
        throw std::runtime_error("Could not load texture: " + path);

    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture(
            SDL_CreateTextureFromSurface(renderer.get(), surface), &SDL_DestroyTexture);

    SDL_FreeSurface(surface);

    if (!texture)
        throw std::runtime_error("could not create texture from surface: " + path);

    textures.emplace(name, std::move(texture));
    return textures.find(name)->second.get();
}

template<>
[[maybe_unused]] TTF_Font *sym::Game::load(const std::string &name, const std::string &path, int args) {
    auto it = fonts.find(name);
    if (it != fonts.end()) return it->second.get();

    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font(
            TTF_OpenFont(path.c_str(), args),
            &TTF_CloseFont);

    if (!font)
        throw std::runtime_error("Could not load font: " + path);

    fonts.emplace(name, std::move(font));
    return fonts.find(name)->second.get();
}

template<typename T>
[[maybe_unused]] T sym::Game::get([[maybe_unused]] const std::string &name) {
    return nullptr;
}

template<>
[[maybe_unused]] SDL_Texture *sym::Game::get(const std::string &name) {
    auto it = textures.find(name);
    if (it == textures.end()) return nullptr;

    return it->second.get();
}

template<>
[[maybe_unused]] TTF_Font *sym::Game::get(const std::string &name) {
    auto it = fonts.find(name);
    if (it == fonts.end()) return nullptr;

    return it->second.get();
}

template<typename T>
[[maybe_unused]] T sym::Game::put([[maybe_unused]] const std::string &name, [[maybe_unused]] T what) {
}

template<>
[[maybe_unused]] SDL_Texture *sym::Game::put(const std::string &name, SDL_Texture *what) {
    if (!what) return nullptr;

    auto deleter = &SDL_DestroyTexture;
    std::unique_ptr<SDL_Texture, decltype(deleter)> new_texture{what, deleter};
    textures.emplace(name, std::move(new_texture));
    return textures.find(name)->second.get();
}

template<>
[[maybe_unused]] TTF_Font *sym::Game::put(const std::string &name, TTF_Font *what) {
    if (!what) return nullptr;

    auto deleter = &TTF_CloseFont;
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> new_font{what, deleter};
    fonts.emplace(name, std::move(new_font));
    return fonts.find(name)->second.get();
}

template<typename T>
[[maybe_unused]] void sym::Game::free([[maybe_unused]] const std::string &name) {
}

template<>
[[maybe_unused]] void sym::Game::free<SDL_Texture *>(const std::string &name) {
    textures.erase(name);
}

template<>
[[maybe_unused]] void sym::Game::free<TTF_Font *>(const std::string &name) {
    fonts.erase(name);
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

void sym::Game::handleEvents(SDL_Event &event) const {
    if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SHOWN) {
        int current_window_width, current_window_height;
        int renderer_width, renderer_height;
        SDL_GetWindowSize(Game::window.get(), &current_window_width, &current_window_height);
        SDL_GetRendererOutputSize(Game::renderer.get(), &renderer_width, &renderer_height);

        pixel_per_pixel = std::make_pair(
                static_cast<float>(renderer_width) / static_cast<float>(window_width),
                static_cast<float>(renderer_height) / static_cast<float>(window_height));
    }
}
