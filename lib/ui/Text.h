#ifndef SYMPHONIA_TEXT_H
#define SYMPHONIA_TEXT_H

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Node.h"

namespace sym::ui {

    class [[maybe_unused]] Text : public Node {
    public:
        Text() = default;
        [[maybe_unused]] Text(const std::string &font_name, const std::string &text);

        void setFont(const std::string &font_name);
        void setText(const std::string &text);

        [[maybe_unused]] void alignText(Anchor target);

        [[maybe_unused]] void draw();

        bool visible = true;
        SDL_Color color{255, 255, 255, 255};

    private:
        TTF_Font *font{nullptr};
        SDL_Rect rect{0, 0, 0, 0};
        Anchor text_align = Anchor::None;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture{nullptr, SDL_DestroyTexture};
    };

}

#endif //SYMPHONIA_TEXT_H
