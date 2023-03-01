#ifndef SYMPHONIA_BUTTON_H
#define SYMPHONIA_BUTTON_H

#include <SDL2/SDL.h>

#include "Node.h"

namespace sym::ui {

    enum class Interaction {
        None,
        Hovering,
        Pressing,
    };

    class [[maybe_unused]] Button : public Node {
    public:
        std::function<void()> onClick;

        bool visible = true;
        bool enabled = true;

        [[maybe_unused]] void input(SDL_Event &event);
        [[maybe_unused]] void draw();

        [[maybe_unused]] void setTexture(Interaction status, SDL_Texture *texture);

    private:
        SDL_Rect rect;
        Interaction current_interaction = Interaction::None;
        SDL_Texture *texture, *texture_hover, *texture_pressed;
    };

}

#endif //SYMPHONIA_BUTTON_H
