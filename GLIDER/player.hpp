#pragma once

#include <SFML/Graphics.hpp>

namespace krv {

    class Player : public sf::RectangleShape {
        sf::Texture texture;

      public:
        Player();
    };

}