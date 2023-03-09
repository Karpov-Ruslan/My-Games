#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace krv {

    Player::Player() {
        setSize(sf::Vector2f(0.9f, 0.9f));
        setOrigin(getSize()/2.0f);
        setPosition(sf::Vector2f(0.0f, 0.0f));
        texture.loadFromFile("../pic/player.png");
        setTexture(&texture);
    }

    void Player::update(const float d_time) {
        bool left, right;
        left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        if (left && right) {v_x = 0.0f;}
        else if (left) {v_x = -7.5f;}
        else if (right) {v_x = 7.5f;}
        else {v_x = 0.0f;}
        if (std::abs(v_y) < 80.0f) {
            if (on_wall) {v_y += gravity*d_time/4.0f;}
            else {v_y += gravity*d_time;}
        }
        move(v_x*d_time, v_y*d_time);

        jump = false;
        on_floor = false;
        on_wall = false;
    }

}