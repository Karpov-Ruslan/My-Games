#ifndef CITY_PLAYER_HPP
#define CITY_PLAYER_HPP

#include <SFML/Graphics.hpp>

const float player_size_x = 40.0f;
const float player_size_y = 40.0f;
const float vertical_push_speed = 1028.0f;
const float G = 2938.0f;

using namespace sf;

class Player {
    Texture texture;
public:
    RectangleShape sprite;
    float vertical_speed;
    float score;

    Player(float x, float y);

    void player_game_cycle(RenderWindow &window, float game_time);

    void player_change_speed();

};


#endif //CITY_PLAYER_HPP
