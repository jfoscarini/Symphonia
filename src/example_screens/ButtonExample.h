#ifndef SYMPHONIA_BUTTONEXAMPLE_H
#define SYMPHONIA_BUTTONEXAMPLE_H

#include "../../lib/Screen.h"
#include "../../lib/ui/Button.h"

class [[maybe_unused]] ButtonExample : public sym::Screen {
public:
    ButtonExample();

    void input(SDL_Event &event) override;
    void update() override;
    void draw() override;
    bool alive() override;

    void buttonClick();

private:
    sym::ui::Button button;
};

#endif //SYMPHONIA_BUTTONEXAMPLE_H
