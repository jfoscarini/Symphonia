#ifndef SYMPHONIA_NODE_H
#define SYMPHONIA_NODE_H

#include <vector>

#include <SDL2/SDL.h>

namespace sym::ui {

    enum class Anchor {
        None,
        TopLeft,
        Top,
        TopRight,
        CenterLeft,
        Center,
        CenterRight,
        BottomLeft,
        Bottom,
        BottomRight,
    };

    class [[maybe_unused]] Node {
    public:
        [[maybe_unused]] void attachTo(Node *target);
        [[maybe_unused]] void attachTo(Anchor target);
        [[maybe_unused]] void detach();

        [[maybe_unused]] void setPosition(SDL_Point offset);
        SDL_Point position();

    private:
        Node *node_parent = nullptr;
        std::function<SDL_Point(SDL_Point nodePosition, int width, int height)> node_anchor;
        SDL_Point node_position{0, 0};

        static std::array<std::function<SDL_Point(SDL_Point nodePosition, int width, int height)>, 10> anchorFunctions;
    };

}

#endif //SYMPHONIA_NODE_H
