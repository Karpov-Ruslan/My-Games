#include "Moveground.hpp"

Moveground::Moveground(float x, float y, std::string string, const RenderWindow &window) : Background(x, y, string) {
    sprite.setPosition(0.0f, window.getSize().y - sprite.getSize().y);
}

void Moveground::horizontal_move(float horizontal_delta, const RenderWindow &window) {
    sprite.move(-horizontal_delta, 0.0f);
    if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width < window.getSize().x) {
        sprite.setPosition(0.0f, window.getSize().y - sprite.getSize().y);
    }
}