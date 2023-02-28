#pragma once

#include<SFML/Graphics.hpp>

namespace krv {

class Background : public sf::RectangleShape {
  public:
    Background(sf::RenderWindow &window, sf::Texture &texture) {
        setSize(sf::Vector2f(800.0f, 600.0f));
        setTexture(&texture);
    }

};




}