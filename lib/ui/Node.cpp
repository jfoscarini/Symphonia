#include "Node.h"
#include "../Game.h"

[[maybe_unused]] void sym::ui::Node::attachTo(sym::ui::Node *target) {
    node_parent = target;
    node_anchor = Anchor::None;
}

[[maybe_unused]] void sym::ui::Node::attachTo(sym::ui::Anchor target) {
    node_parent = nullptr;
    node_anchor = target;
}

[[maybe_unused]] void sym::ui::Node::detach() {
    node_parent = nullptr;
    node_anchor = Anchor::None;
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

    if (node_anchor == Anchor::None) return node_position;

    int width, height;
    SDL_GetRendererOutputSize(Game::renderer.get(), &width, &height);
    switch (node_anchor) {
        case Anchor::TopLeft: return {node_position.x, node_position.y};
        case Anchor::Top: return {node_position.x + width / 2, node_position.y};
        case Anchor::TopRight: return {node_position.x + width, node_position.y};
        case Anchor::CenterLeft: return {node_position.x, node_position.y + height / 2};
        case Anchor::Center: return {node_position.x + width / 2, node_position.y + height / 2};
        case Anchor::CenterRight: return {node_position.x + width, node_position.y + height / 2};
        case Anchor::BottomLeft: return {node_position.x, node_position.y + height};
        case Anchor::Bottom: return {node_position.x + width / 2, node_position.y + height};
        case Anchor::BottomRight: return {node_position.x + width, node_position.y + height};
        default: return {0, 0};
    }
}
