#include "Button.h"
#include "../Game.h"

void sym::ui::Button::input(SDL_Event &event) {
    if (!enabled) return;
    if (event.type != SDL_MOUSEMOTION && event.type != SDL_MOUSEBUTTONDOWN && event.type != SDL_MOUSEBUTTONUP)
        return;

    SDL_Rect target = rect;
    auto position = Node::position();
    target.x += position.x;
    target.y += position.y;

    const SDL_Point mouse_position = Game::getRelativeMousePosition(event.motion.x, event.motion.y);
    if (!SDL_PointInRect(&mouse_position, &target)) {
        current_interaction = Interaction::None;
        return;
    }

    if (event.type == SDL_MOUSEMOTION && current_interaction == Interaction::None) {
        current_interaction = Interaction::Hovering;
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        current_interaction = Interaction::Pressing;
    } else if (event.type == SDL_MOUSEBUTTONUP && current_interaction == Interaction::Pressing) {
        current_interaction = Interaction::Hovering;
        if (onClick) onClick();
    }
}

void sym::ui::Button::draw() {
    if (!visible) return;

    SDL_Rect target = rect;
    auto position = Node::position();
    target.x += position.x;
    target.y += position.y;

    switch (current_interaction) {
        case Interaction::None:
            if (texture) SDL_RenderCopy(sym::Game::renderer.get(), texture, nullptr, &target);
            break;
        case Interaction::Hovering:
            if (texture_hover) SDL_RenderCopy(sym::Game::renderer.get(), texture_hover, nullptr, &target);
            else if (texture) SDL_RenderCopy(sym::Game::renderer.get(), texture, nullptr, &target);
            break;
        case Interaction::Pressing:
            if (texture_pressed) SDL_RenderCopy(sym::Game::renderer.get(), texture_pressed, nullptr, &target);
            else if (texture_hover) SDL_RenderCopy(sym::Game::renderer.get(), texture_hover, nullptr, &target);
            else if (texture) SDL_RenderCopy(sym::Game::renderer.get(), texture, nullptr, &target);
    }
}

void sym::ui::Button::setTexture(sym::ui::Interaction status, SDL_Texture *new_texture) {
    switch (status) {
        case Interaction::None:
            SDL_QueryTexture(new_texture, nullptr, nullptr, &rect.w, &rect.h);
            texture = new_texture;
            break;
        case Interaction::Hovering:
            texture_hover = new_texture;
            break;
        case Interaction::Pressing:
            texture_pressed = new_texture;
            break;
        default:
            break;
    }
}
