#ifndef SYMPHONIA_TEXTEXAMPLE_H
#define SYMPHONIA_TEXTEXAMPLE_H

#include "../../lib/Screen.h"
#include "../../lib/ui/Text.h"

class [[maybe_unused]] TextExample : public sym::Screen {
public:
    TextExample();

    void input(SDL_Event &event) override;
    void update() override;
    void draw() override;
    bool alive() override;

private:
    sym::ui::Text text;
};

#endif //SYMPHONIA_TEXTEXAMPLE_H
