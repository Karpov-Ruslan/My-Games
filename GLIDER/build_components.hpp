#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "game_objects.hpp"

namespace krv {

class Build_Cursor : public sf::Drawable {
    bool pressed = false;
    sf::Vector2f pos;
    sf::Vector2f old_pos;
    sf::Texture texture;
    sf::RectangleShape cursor;
    sf::RectangleShape rect;
    GAME_OBJECT_TYPE type = GAME_OBJECT_TYPE::NOTHING;
  public:
    Build_Cursor(float length, sf::Color color = sf::Color(255, 255, 255, 75)) {
        cursor.setOrigin(sf::Vector2f(length/2.0f, length/2.0f));
        cursor.setSize(sf::Vector2f(length, length));
        texture.loadFromFile("../pic/Glider/build_cursor.png");
        cursor.setTexture(&texture);
        rect.setFillColor(color);
    }

    sf::Vector2f get_pos() const {
        return pos;
    }

    GAME_OBJECT_TYPE get_type() const {
        return type;
    }

    void decrease_type() {
        if (type == GAME_OBJECT_TYPE::BLOCK) {
            type = GAME_OBJECT_TYPE::NOTHING;
        }
        else {
            type = static_cast<GAME_OBJECT_TYPE>(static_cast<int>(type) - 1);
        }
        pressed = false;
    }

    void increase_type() {
        if (type == GAME_OBJECT_TYPE::NOTHING) {
            type = GAME_OBJECT_TYPE::BLOCK;
        }
        else {
            type = static_cast<GAME_OBJECT_TYPE>(static_cast<int>(type) + 1);
        }
        pressed = false;
    }

    bool get_pressed() const {
        return pressed;
    }

    sf::FloatRect get_floatrect() const {
        return rect.getGlobalBounds();
    }

    void change_press() {
        if (type != GAME_OBJECT_TYPE::NOTHING) {
            pressed = !pressed;
            if (pressed) {
                rect.setSize(cursor.getSize());
                rect.setOrigin(rect.getSize()/2.0f);
                old_pos = cursor.getPosition();
                rect.setPosition(old_pos);
            }
        }
    }

    void update(sf::RenderWindow &window, const sf::View &view) {
        sf::Vector2f world_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
        sf::Vector2f round_world_pos = sf::Vector2f(std::round(world_pos.x), std::round(world_pos.y));
        cursor.setPosition(round_world_pos);
        if (pressed) {
            rect.setSize(sf::Vector2f(std::abs(round_world_pos.x - old_pos.x) + 1.0f, std::abs(round_world_pos.y - old_pos.y) + 1.0f));
            rect.setOrigin(rect.getSize()/2.0f);
            rect.setPosition((round_world_pos + old_pos)/2.0f);
        }
    }

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (pressed) {
            target.draw(rect, states);
        }
        target.draw(cursor, states);
    }
};






}