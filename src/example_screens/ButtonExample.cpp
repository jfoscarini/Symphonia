#include <string>

#include "ButtonExample.h"
#include "../../lib/Game.h"

ButtonExample::ButtonExample() {
    button.attachTo(sym::ui::Anchor::Center);

    button.onClick = [this] { buttonClick(); };

    button.setTexture(
            sym::ui::Interaction::None,
            sym::Game::load<SDL_Texture *>("button", "../assets/button.png"));
    button.setTexture(
            sym::ui::Interaction::Hovering,
            sym::Game::load<SDL_Texture *>("button_hover", "../assets/button_hover.png"));
    button.setTexture(
            sym::ui::Interaction::Pressing,
            sym::Game::load<SDL_Texture *>("button_pressed", "../assets/button_pressed.png"));
}

void ButtonExample::input(SDL_Event &event) {
    button.input(event);
}

void ButtonExample::update() {

}

void ButtonExample::draw() {
    button.draw();
}

bool ButtonExample::alive() {
    return true;
}

void ButtonExample::buttonClick() {
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);
}
