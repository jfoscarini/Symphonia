#include "Node.h"
#include "../Game.h"

[[maybe_unused]] void sym::ui::Node::attachTo(sym::ui::Node *target) {
    node_parent = target;
}

[[maybe_unused]] void sym::ui::Node::detach() {
    node_parent = nullptr;
}

[[maybe_unused]] void sym::ui::Node::attachTo(sym::ui::Anchor target) {
    node_parent = nullptr;
    int width, height;
    SDL_GetRendererOutputSize(Game::renderer.get(), &width, &height);

    switch (target) {
        case Anchor::TopLeft:
            node_position = {0, 0};
            break;
        case Anchor::Top:
            node_position = {width / 2, 0};
            break;
        case Anchor::TopRight:
            node_position = {width, 0};
            break;
        case Anchor::CenterLeft:
            node_position = {0, height / 2};
            break;
        case Anchor::Center:
            node_position = {width / 2, height / 2};
            break;
        case Anchor::CenterRight:
            node_position = {width, height / 2};
            break;
        case Anchor::BottomLeft:
            node_position = {0, height};
            break;
        case Anchor::Bottom:
            node_position = {width / 2, height};
            break;
        case Anchor::BottomRight:
            node_position = {width, height};
            break;
    }
}

[[maybe_unused]] void sym::ui::Node::setPosition(SDL_Point offset) {
    node_position = offset;
}

SDL_Point sym::ui::Node::position() {
    auto position = node_position;
    if (node_parent) {
        auto parent_position = node_parent->position();
        position.x += parent_position.x;
        position.y += parent_position.y;
    }

    return position;
}
