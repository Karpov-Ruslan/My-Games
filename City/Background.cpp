#include "Background.hpp"

Background::Background(float x, float y, std::string string) {
    sprite.setSize( Vector2f(x, y) );
    texture.loadFromFile(string);
    sprite.setTexture(&texture);
}

Background::Background(RenderWindow const &window, std::string string) {
sprite.setSize( Vector2f(window.getSize().x, window.getSize().y) );
texture.loadFromFile(string);
sprite.setTexture(&texture);
}