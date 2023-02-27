#ifndef SYMPHONIA_TITLESCREEN_H
#define SYMPHONIA_TITLESCREEN_H

#include "../../lib/Screen.h"

class TitleScreen : public sym::Screen {
public:
    TitleScreen() = default;

    void input(SDL_Event &event) override;
    void update() override;
    void draw() override;
    bool alive() override;
private:
};

#endif //SYMPHONIA_TITLESCREEN_H
