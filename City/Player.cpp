#include "Player.hpp"

Player::Player(float x, float y) {
    sprite.setOrigin(player_size_x/2.0f, player_size_y/2.0f);
    sprite.setPosition(x, y);
    sprite.setSize(Vector2f(player_size_x, player_size_y));
    texture.loadFromFile("../pic/player.png");
    sprite.setTexture(&texture);
    vertical_speed = 100.0f;
    score = 0;
}

void Player::player_game_cycle(RenderWindow &window, float game_time) {
    sprite.move(0.0f, -vertical_speed*game_time);
    vertical_speed -= G*game_time;
    if (sprite.getGlobalBounds().top < 0.0f) {
        sprite.move(0.0f, -sprite.getGlobalBounds().top);
    }

    if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height > 800.0f) {
        sprite.move(0.0f, 800.0f - ( sprite.getGlobalBounds().top + sprite.getGlobalBounds().height ));
    }
}

void Player::player_change_speed() {
    vertical_speed = vertical_push_speed;
}