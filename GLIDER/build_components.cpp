#include "build_components.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include "game_objects.hpp"

namespace krv {

const float scale = 50.0f;

Build_Type::Build_Type() {
    int number = static_cast<int>(GAME_OBJECT_TYPE::NOTHING) + 1;
    types_texture.loadFromFile("../pic/Glider/game_objects.png");
    types.setSize(sf::Vector2f(number*scale, scale));
    types.setTexture(&types_texture);
    select.setSize(sf::Vector2f(scale, scale));
    select.setPosition(0.0f, 0.0f);
    select_texture.loadFromFile("../pic/Glider/build_cursor.png");
    select.setTexture(&select_texture);
}

void Build_Type::update(GAME_OBJECT_TYPE type) {
    select.setPosition(static_cast<int>(type)*scale, 0.0f);
}

void Build_Type::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(types, states);
    target.draw(select, states);
}



Build_Cursor::Build_Cursor(float length, sf::Color color) {
    cursor.setOrigin(sf::Vector2f(length/2.0f, length/2.0f));
    cursor.setSize(sf::Vector2f(length, length));
    texture.loadFromFile("../pic/Glider/direct_build_cursor.png");
    cursor.setTexture(&texture);
    rect.setFillColor(color);
    rect.setOutlineColor(sf::Color::Black);
}

sf::Vector2f Build_Cursor::get_pos() const {
    return pos;
}

GAME_OBJECT_TYPE Build_Cursor::get_type() const {
    return type;
}

float Build_Cursor::get_rotation() const {
    return cursor.getRotation();
}

void Build_Cursor::rotate() {
    cursor.rotate(90.0f);
    if (cursor.getRotation() > 315.0f) {
        cursor.setRotation(0.0f);
    }
}

void Build_Cursor::decrease_type() {
    if (type == GAME_OBJECT_TYPE::BLOCK) {
        type = GAME_OBJECT_TYPE::NOTHING;
    }
    else {
        type = static_cast<GAME_OBJECT_TYPE>(static_cast<int>(type) - 1);
    }
    pressed = false;
}

void Build_Cursor::increase_type() {
    if (type == GAME_OBJECT_TYPE::NOTHING) {
        type = GAME_OBJECT_TYPE::BLOCK;
    }
    else {
        type = static_cast<GAME_OBJECT_TYPE>(static_cast<int>(type) + 1);
    }
    pressed = false;
}

bool Build_Cursor::get_pressed() const {
    return pressed;
}

sf::FloatRect Build_Cursor::get_floatrect() const {
    return rect.getGlobalBounds();
}

void Build_Cursor::change_press() {
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

void Build_Cursor::update(sf::RenderWindow &window, const sf::View &view) {
    sf::Vector2f world_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
    sf::Vector2f round_world_pos = sf::Vector2f(std::round(world_pos.x), std::round(world_pos.y));
    cursor.setPosition(round_world_pos);
    if (pressed) {
        float x = std::abs(round_world_pos.x - old_pos.x) + 1.0f;
        float y = std::abs(round_world_pos.y - old_pos.y) + 1.0f;
        rect.setSize(sf::Vector2f(x, y));
        rect.setOrigin(rect.getSize()/2.0f);
        rect.setPosition((round_world_pos + old_pos)/2.0f);
        if (x < build_cursor_size_red && y < build_cursor_size_red) {
            if (static_cast<int>(x) == static_cast<int>(y)) {
                rect.setFillColor(sf::Color(0, 255, 255, 100));
            }
            else {
                rect.setFillColor(sf::Color(255, 255, 255, 100));
            }
        }
        else {
            rect.setFillColor(sf::Color(255, 0, 0, 100));
        }
    }
}

void Build_Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (pressed) {
        target.draw(rect, states);
    }
    target.draw(cursor, states);
}






}