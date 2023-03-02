#pragma once

#include <SFML/Graphics.hpp>
#include "game_objects.hpp"

namespace krv {

class Build_Type : public sf::Drawable {
    sf::Texture types_texture;
    sf::Texture select_texture;
    sf::RectangleShape types;
    sf::RectangleShape select;

  public:
    Build_Type();

    void update(GAME_OBJECT_TYPE type);

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


class Build_Cursor : public sf::Drawable {
    bool pressed = false;
    sf::Vector2f pos;
    sf::Vector2f old_pos;
    sf::Texture texture;
    sf::RectangleShape cursor;
    sf::RectangleShape rect;
    GAME_OBJECT_TYPE type = GAME_OBJECT_TYPE::BLOCK;
  public:
    Build_Cursor(float length, sf::Color color = sf::Color(255, 255, 255, 100));

    sf::Vector2f get_pos() const;

    GAME_OBJECT_TYPE get_type() const;

    float get_rotation() const;

    void rotate();

    void decrease_type();

    void increase_type();

    bool get_pressed() const;

    sf::FloatRect get_floatrect() const;

    void change_press();

    void update(sf::RenderWindow &window, const sf::View &view);

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};






}