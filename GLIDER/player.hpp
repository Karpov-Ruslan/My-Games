#pragma once

#include <SFML/Graphics.hpp>

namespace krv {

    const float gravity = 54.0f;

    class Player : public sf::RectangleShape {
        sf::Texture texture;
      public:
        float jump_waiting_time = 0.0f;
        float v_x = 0.0f;
        float v_y = 0.0f;
        bool on_floor = false;
        bool on_wall = false;
        bool death = false;
        bool finish = false;


        Player();

        void update(const float d_time);
    };

}