#include <string>

#include "TextExample.h"
#include "../../lib/Game.h"

TextExample::TextExample() {
    sym::Game::loadFont("upheaval24", 100, "../assets/UpheavalPro.ttf");

    text.attachTo(sym::ui::Anchor::Center);
    text.alignText(sym::ui::Anchor::Center);

    text.setFont("upheaval24");
    text.setText("Hello World!");
}

void TextExample::input(SDL_Event &event) {

}

void TextExample::update() {

}

void TextExample::draw() {
    text.draw();
}

bool TextExample::alive() {
    return true;
}
