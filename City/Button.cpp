#include "Button.hpp"

Button::Button(float pos_x, float pos_y, float delta_x, float delta_y, std::string string) {
    sprite.setSize( Vector2f(delta_x, delta_y) );
    sprite.setOrigin( sprite.getSize()/2.0f );
    sprite.setPosition(pos_x, pos_y);
    texture.loadFromFile(string);
    sprite.setTexture(&texture);
}

bool Button::point_on(float x, float y) {
    if (sprite.getGlobalBounds().contains(x, y)) {
        return true;
    }
    return false;
}

bool Button::smth_pressed_on(float x, float y, Event &event) {
    if (sprite.getGlobalBounds().contains(x, y) && (event.type == Event::MouseButtonPressed || event.type == Event::KeyPressed) ) {
        return true;
    }
    return false;
}