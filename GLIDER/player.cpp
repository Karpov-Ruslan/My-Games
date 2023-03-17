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

    const float jump_wait_time = 0.5f;
    const float speed_x = 10.0f;

    void Player::update(const float d_time) {
        bool slow = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
        bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        bool jump = (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)));
        bool jump_time = !(jump_waiting_time > 0.0f);

        if (left && right) {v_x = 0.0f;}
        else if (left) {v_x = -speed_x;}
        else if (right) {v_x = speed_x;}
        else {v_x = 0.0f;}
        if (slow) {v_x /= 4.0f;
        }
        if (!jump_time) {
            jump_waiting_time -= d_time;
        }
        if (jump && on_floor) { //Jump from floor
            v_y = -20.0f;
            on_floor = false;
            jump = false;
            jump_waiting_time = jump_wait_time;
        }
        else if (jump_time && jump && on_wall) { //Jump from wall
            v_y = -20.0f;
            on_wall = false;
            jump_waiting_time = jump_wait_time;
        }
        if (std::abs(v_y) < 80.0f) {
            v_y += gravity*d_time;
        }
        move(v_x*d_time, v_y*d_time);
        on_floor = false;
        on_wall = false;
    }

}