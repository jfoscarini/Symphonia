#include <array>

#include "Node.h"
#include "../Game.h"

[[maybe_unused]] void sym::ui::Node::attachTo(sym::ui::Node *target) {
    node_parent = target;
    node_anchor = nullptr;
}

[[maybe_unused]] void sym::ui::Node::attachTo(sym::ui::Anchor target) {
    node_parent = nullptr;

    auto idx = static_cast<std::size_t>(target);
    if (idx < anchorFunctions.size()) node_anchor = anchorFunctions[idx];
}

[[maybe_unused]] void sym::ui::Node::detach() {
    node_parent = nullptr;
    node_anchor = nullptr;
}

[[maybe_unused]] void sym::ui::Node::setPosition(SDL_Point offset) {
    node_position = offset;
}

SDL_Point sym::ui::Node::position() {
    if (node_parent) {
        auto parent_position = node_parent->position();
        return {
                node_position.x + parent_position.x,
                node_position.y + parent_position.y,
        };
    }

    if (!node_anchor) return node_position;

    int width, height;
    SDL_GetRendererOutputSize(Game::renderer.get(), &width, &height);
    return node_anchor(node_position, width, height);
}

std::array<std::function<SDL_Point(SDL_Point nodePosition, int width, int height)>, 10> sym::ui::Node::anchorFunctions = {
        nullptr,
        nullptr,
        [](SDL_Point nodePosition, int width, int height) { return SDL_Point{nodePosition.x + width / 2, nodePosition.y}; },
        [](SDL_Point nodePosition, int width, int height) { return SDL_Point{nodePosition.x + width, nodePosition.y}; },
        [](SDL_Point nodePosition, int width, int height) { return SDL_Point{nodePosition.x, nodePosition.y + height / 2}; },
        [](SDL_Point nodePosition, int width, int height) { return SDL_Point{nodePosition.x + width / 2, nodePosition.y + height / 2}; },
        [](SDL_Point nodePosition, int width, int height) { return SDL_Point{nodePosition.x + width, nodePosition.y + height / 2}; },
        [](SDL_Point nodePosition, int width, int height) { return SDL_Point{nodePosition.x, nodePosition.y + height}; },
        [](SDL_Point nodePosition, int width, int height) { return SDL_Point{nodePosition.x + width / 2, nodePosition.y + height}; },
        [](SDL_Point nodePosition, int width, int height) { return SDL_Point{nodePosition.x + width, nodePosition.y + height}; }
};
