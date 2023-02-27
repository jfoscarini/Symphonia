#include "../lib/Game.h"
#include "screens/TitleScreen.h"

int main() {
    auto game = sym::Game();

    sym::Game::new_screens.push_back(std::make_unique<TitleScreen>());

    game.run();

    return 0;
}
