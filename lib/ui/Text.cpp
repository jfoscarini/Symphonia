#include <string>
#include <array>

#include "Text.h"
#include "../Game.h"

[[maybe_unused]] sym::ui::Text::Text(const std::string &font_name, const std::string &text) {
    setFont(font_name);
    setText(text);
}

void sym::ui::Text::setFont(const std::string &font_name) {
    font = Game::get<TTF_Font *>(font_name);
    if (!font) SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not find font: \"%s\".", font_name.c_str());
}

void sym::ui::Text::setText(const std::string &text) {
    if (!font) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Cannot write \"%s\" when font is null.", text.c_str());
        return;
    }

    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text.c_str(), {255, 255, 255, 255});
    if (!surface) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not create surface when writing \"%s\".", text.c_str());
        return;
    }

    texture.reset(SDL_CreateTextureFromSurface(Game::renderer.get(), surface));
    SDL_FreeSurface(surface);

    if (!texture) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not create texture from text: \"%s\".", text.c_str());
        return;
    }

    if (SDL_QueryTexture(texture.get(), nullptr, nullptr, &rect.w, &rect.h) != 0)
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not query texture for text: \"%s\".", text.c_str());
}

[[maybe_unused]] void sym::ui::Text::alignText(sym::ui::Anchor target) {
    auto idx = static_cast<std::size_t>(target);
    if (idx < alignmentFunctions.size()) text_align = alignmentFunctions[idx];
}

[[maybe_unused]] void sym::ui::Text::draw() {
    if (!visible || !texture) return;

    SDL_Rect target = rect;
    auto position = Node::position();
    target.x += position.x;
    target.y += position.y;

    if (text_align) text_align(target);

    SDL_SetTextureColorMod(texture.get(), color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(texture.get(), color.a);
    SDL_RenderCopy(Game::renderer.get(), texture.get(), nullptr, &target);
}

std::array<std::function<void(SDL_Rect &target)>, 10> sym::ui::Text::alignmentFunctions = {
        nullptr,
        nullptr,
        [](SDL_Rect &target) { target.x -= target.w / 2; },
        [](SDL_Rect &target) { target.x -= target.w; },
        [](SDL_Rect &target) { target.y -= target.h / 2; },
        [](SDL_Rect &target) { target.x -= target.w / 2; target.y -= target.h / 2; },
        [](SDL_Rect &target) { target.x -= target.w; target.y -= target.h / 2; },
        [](SDL_Rect &target) { target.y -= target.h; },
        [](SDL_Rect &target) { target.x -= target.w / 2; target.y -= target.h;},
        [](SDL_Rect &target) { target.x -= target.w; target.y -= target.h;}
};
