#include <catch2/catch_test_macros.hpp>

#include "../lib/ui/Node.h"
#include "../lib/Game.h"

TEST_CASE("Node is properly initialized", "[Node]") {
    auto game = sym::Game();
    sym::ui::Node node;
    auto position = node.position();

    CHECK(position.x == 0);
    CHECK(position.y == 0);
}

TEST_CASE("Node is properly attached", "[Node]") {
    auto game = sym::Game();

    SDL_Point child_position;
    sym::ui::Node parent;
    parent.setPosition({10, 10});

    sym::ui::Node child;
    child.attachTo(&parent);
    child.setPosition({15, -15});

    child_position = child.position();
    CHECK(child_position.x == 25);
    CHECK(child_position.y == -5);

    parent.setPosition({20, 20});

    child_position = child.position();
    CHECK(child_position.x == 35);
    CHECK(child_position.y == 5);
}

TEST_CASE("Node is properly anchored", "[Node]") {
    auto game = sym::Game();
    sym::ui::Node node;
    SDL_Point position;

    int width, height;
    SDL_GetRendererOutputSize(sym::Game::renderer.get(), &width, &height);

    node.attachTo(sym::ui::Anchor::TopLeft);
    position = node.position();
    CHECK(position.x == 0);
    CHECK(position.y == 0);

    node.attachTo(sym::ui::Anchor::Top);
    position = node.position();
    CHECK(position.x == width / 2);
    CHECK(position.y == 0);

    node.attachTo(sym::ui::Anchor::TopRight);
    position = node.position();
    CHECK(position.x == width);
    CHECK(position.y == 0);

    node.attachTo(sym::ui::Anchor::CenterLeft);
    position = node.position();
    CHECK(position.x == 0);
    CHECK(position.y == height / 2);

    node.attachTo(sym::ui::Anchor::Center);
    position = node.position();
    CHECK(position.x == width / 2);
    CHECK(position.y == height / 2);

    node.attachTo(sym::ui::Anchor::CenterRight);
    position = node.position();
    CHECK(position.x == width);
    CHECK(position.y == height / 2);

    node.attachTo(sym::ui::Anchor::BottomLeft);
    position = node.position();
    CHECK(position.x == 0);
    CHECK(position.y == height);

    node.attachTo(sym::ui::Anchor::Bottom);
    position = node.position();
    CHECK(position.x == width / 2);
    CHECK(position.y == height);

    node.attachTo(sym::ui::Anchor::BottomRight);
    position = node.position();
    CHECK(position.x == width);
    CHECK(position.y == height);
}
