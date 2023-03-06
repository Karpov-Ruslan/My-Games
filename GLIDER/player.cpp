#include "player.hpp"
#include <SFML/Graphics.hpp>

namespace krv {

    Player::Player() {
        setSize(sf::Vector2f(0.9f, 0.9f));
        setOrigin(getSize()/2.0f);
        setPosition(sf::Vector2f(0.0f, 0.0f));
        texture.loadFromFile("../pic/player.png");
        setTexture(&texture);
    }

}