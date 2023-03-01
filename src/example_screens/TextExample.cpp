#include <string>

#include "TextExample.h"
#include "../../lib/Game.h"

TextExample::TextExample() {
    sym::Game::load<TTF_Font *>("upheaval100", "../assets/UpheavalPro.ttf", 100);

    text.attachTo(sym::ui::Anchor::Center);
    text.alignText(sym::ui::Anchor::Center);

    text.setFont("upheaval100");
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
