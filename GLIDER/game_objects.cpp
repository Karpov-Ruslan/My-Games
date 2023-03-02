#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <vector>
#include <utility>

#include "game_objects.hpp"

namespace krv {

const int factor = 50;

class Colors : public sf::Drawable {
    std::vector<sf::RectangleShape> color_array;
    sf::RectangleShape select;
    bool selected = false;

    void constructor_helper(sf::Color color) {
        sf::RectangleShape shape(sf::Vector2f(700.0f, 40.0f));
        shape.setPosition(50.0f, 40.0f + 80.0f*color_array.size());
        shape.setFillColor(color);
        color_array.push_back(std::move(shape));
    }

  public:
    Colors() {
        constructor_helper(sf::Color::Red);
        constructor_helper(sf::Color(255, 102, 0, 255));
        constructor_helper(sf::Color::Yellow);
        constructor_helper(sf::Color::Green);
        constructor_helper(sf::Color::Blue);
        constructor_helper(sf::Color::Magenta);
        constructor_helper(sf::Color::White);
        select.setFillColor(sf::Color(0, 0, 0, 100));
        select.setSize(sf::Vector2f(700.0f, 40.0f));
    }

    sf::Color update(sf::RenderWindow &window) {
        for (const auto& it : color_array) {
            if (it.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                select.setPosition(it.getPosition());
                selected = true;
                return it.getFillColor();
            }
        }
        selected = false;
        return sf::Color(0, 0, 0, 0);
    }

    bool get_selected() const {
        return selected;
    }

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (const auto& it : color_array) {
            target.draw(it, states);
        }
        if (selected) {
            target.draw(select, states);
        }
    }
};

sf::Color choose_color(sf::RenderWindow &window) {
    sf::View view = window.getView();
    window.setView(window.getDefaultView());
    Colors colors;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (colors.get_selected()) {
                    return colors.update(window);
                }
            }
        }
        colors.update(window);

        window.clear();
        window.draw(colors);
        window.display();
    }
}

void constructor_template(GAME_OBJECT_TYPE type, sf::RectangleShape &value, sf::Texture &texture, const sf::FloatRect &floatrect, const float angle = 0.0f) {
    value.setPosition(floatrect.left, floatrect.top);
    value.setSize(sf::Vector2f(floatrect.width, floatrect.height));

    sf::RenderTexture render_texture;
    int x = static_cast<int>(floatrect.width);
    int y = static_cast<int>(floatrect.height);
    render_texture.create(factor*x, factor*y);
    render_texture.clear(sf::Color(255, 255, 255, 0));
    sf::RectangleShape shape(sf::Vector2f(factor, factor));
    sf::Texture buffer;
    buffer.loadFromFile("../pic/Glider/game_objects.png");
    shape.setTexture(&buffer);
    shape.setTextureRect(sf::IntRect(static_cast<int>(type)*factor, 0, factor, factor));
    shape.rotate(angle);
    shape.setOrigin(shape.getSize()/2.0f);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            shape.setPosition(factor*i + factor/2.0f, factor*j + factor/2.0f);
            render_texture.draw(shape);
        }
    }
    render_texture.display();
    texture = render_texture.getTexture();
    value.setTexture(&texture);
}


bool vertical_direct(const float angle) {
    return ((angle > -45.0f && angle < 45.0f) || (angle > 135.0f && angle < 225.0f));
}





Block::Block(const sf::FloatRect &floatrect) : sf::RectangleShape() {
    constructor_template(GAME_OBJECT_TYPE::BLOCK, (*this), texture, floatrect);
}

Block::Block(const Block& value) : sf::RectangleShape(value) {
    texture = value.texture;
    setTexture(&texture);
}

Block& Block::operator=(const Block& value) {
    (*this).sf::RectangleShape::operator=(value);
    texture = value.texture;
    setTexture(&texture);
    return *this;
}

Block::Block(Block&& value) : sf::RectangleShape(value) {
    texture = std::move(value.texture);
    setTexture(&texture);
}

Block& Block::operator=(Block&& value) {
    (*this).sf::RectangleShape::operator=(std::move(value));
    texture = std::move(value.texture);
    setTexture(&texture);
    return *this;
}




Spike::Spike(const sf::FloatRect &floatrect, const float angle) {
    constructor_template(GAME_OBJECT_TYPE::SPIKE, (*this), texture, floatrect, angle);
}

Spike::Spike(const Spike& value) : sf::RectangleShape(value) {
    texture = value.texture;
    setTexture(&texture);
}

Spike& Spike::operator=(const Spike& value) {
    (*this).sf::RectangleShape::operator=(value);
    texture = value.texture;
    setTexture(&texture);
    return *this;
}

Spike::Spike(Spike&& value) : sf::RectangleShape(value) {
    texture = std::move(value.texture);
    setTexture(&texture);
}

Spike& Spike::operator=(Spike&& value) {
    (*this).sf::RectangleShape::operator=(std::move(value));
    texture = std::move(value.texture);
    setTexture(&texture);
    return *this;
}



Tramplin::Tramplin(const sf::FloatRect &floatrect) {
    constructor_template(GAME_OBJECT_TYPE::TRAMPLIN, (*this), texture, floatrect);
}

Tramplin::Tramplin(const Tramplin& value) : sf::RectangleShape(value) {
    texture = value.texture;
    setTexture(&texture);
}

Tramplin& Tramplin::operator=(const Tramplin& value) {
    (*this).sf::RectangleShape::operator=(value);
    texture = value.texture;
    setTexture(&texture);
    return *this;
}

Tramplin::Tramplin(Tramplin&& value) : sf::RectangleShape(value) {
    texture = std::move(value.texture);
    setTexture(&texture);
}

Tramplin& Tramplin::operator=(Tramplin&& value) {
    (*this).sf::RectangleShape::operator=(std::move(value));
    texture = std::move(value.texture);
    setTexture(&texture);
    return *this;
}



Shuriken::Shuriken(const sf::FloatRect &floatrect) {
    float size_x = floatrect.width, size_y = floatrect.height;
    if (size_x < size_y) {size_y = size_x;}
    else {size_x = size_y;}
    setSize(sf::Vector2f(size_x, size_x));
    setOrigin(getSize()/2.0f);
    setPosition(sf::Vector2f(floatrect.left, floatrect.top) + getOrigin());
    texture.loadFromFile("../pic/Glider/shuriken.png");
    setTexture(&texture);
}

Shuriken::Shuriken(const Shuriken& value) : sf::RectangleShape(value) {
    texture = value.texture;
    setTexture(&texture);
}

Shuriken& Shuriken::operator=(const Shuriken& value) {
    (*this).sf::RectangleShape::operator=(value);
    texture = value.texture;
    setTexture(&texture);
    return *this;
}

Shuriken::Shuriken(Shuriken&& value) : sf::RectangleShape(value) {
    texture = std::move(value.texture);
    setTexture(&texture);
}

Shuriken& Shuriken::operator=(Shuriken&& value) {
    (*this).sf::RectangleShape::operator=(std::move(value));
    texture = std::move(value.texture);
    setTexture(&texture);
    return *this;
}



Stair::Stair(const sf::FloatRect &floatrect, const float angle) {
    //TODO: Remake Constructor texture
    constructor_template(GAME_OBJECT_TYPE::STAIR, (*this), texture, floatrect, angle);
}

Stair::Stair(const Stair& value) : sf::RectangleShape(value) {
    texture = value.texture;
    setTexture(&texture);
}

Stair& Stair::operator=(const Stair& value) {
    (*this).sf::RectangleShape::operator=(value);
    texture = value.texture;
    setTexture(&texture);
    return *this;
}

Stair::Stair(Stair&& value) : sf::RectangleShape(value) {
    texture = std::move(value.texture);
    setTexture(&texture);
}

Stair& Stair::operator=(Stair&& value) {
    (*this).sf::RectangleShape::operator=(std::move(value));
    texture = std::move(value.texture);
    setTexture(&texture);
    return *this;
}

bool Stair::get_vertical() const {
    return vertical;
}



Laser::Laser(const sf::FloatRect &floatrect, const float angle) {
    //TODO: Remake constructor texture
    constructor_template(GAME_OBJECT_TYPE::LASER, (*this), texture, floatrect, angle);
}

Laser::Laser(const Laser& value) : sf::RectangleShape(value) {
    texture = value.texture;
    setTexture(&texture);
}

Laser& Laser::operator=(const Laser& value) {
    (*this).sf::RectangleShape::operator=(value);
    texture = value.texture;
    setTexture(&texture);
    return *this;
}

Laser::Laser(Laser&& value) : sf::RectangleShape(value) {
    texture = std::move(value.texture);
    setTexture(&texture);
}

Laser& Laser::operator=(Laser&& value) {
    (*this).sf::RectangleShape::operator=(std::move(value));
    texture = std::move(value.texture);
    setTexture(&texture);
    return *this;
}



Door::Door(const sf::FloatRect &floatrect, sf::RenderWindow &window) {
    constructor_template(GAME_OBJECT_TYPE::DOOR, (*this), texture, floatrect);
    setFillColor(choose_color(window));
}

Door::Door(const Door& value) : sf::RectangleShape(value) {
    texture = value.texture;
    setTexture(&texture);
}

Door& Door::operator=(const Door& value) {
    (*this).sf::RectangleShape::operator=(value);
    texture = value.texture;
    setTexture(&texture);
    return *this;
}

Door::Door(Door&& value) : sf::RectangleShape(value) {
    texture = std::move(value.texture);
    setTexture(&texture);
}

Door& Door::operator=(Door&& value) {
    (*this).sf::RectangleShape::operator=(std::move(value));
    texture = std::move(value.texture);
    setTexture(&texture);
    return *this;
}



Key::Key(const sf::FloatRect &floatrect, sf::RenderWindow &window) {
    constructor_template(GAME_OBJECT_TYPE::KEY, (*this), texture, floatrect);
    setFillColor(choose_color(window));
}

Key::Key(const Key& value) : sf::RectangleShape(value) {
    texture = value.texture;
    setTexture(&texture);
}

Key& Key::operator=(const Key& value) {
    (*this).sf::RectangleShape::operator=(value);
    texture = value.texture;
    setTexture(&texture);
    return *this;
}

Key::Key(Key&& value) : sf::RectangleShape(value) {
    texture = std::move(value.texture);
    setTexture(&texture);
}

Key& Key::operator=(Key&& value) {
    (*this).sf::RectangleShape::operator=(std::move(value));
    texture = std::move(value.texture);
    setTexture(&texture);
    return *this;
}





void Game_Objects::add(sf::RenderWindow &window, GAME_OBJECT_TYPE type, const sf::FloatRect &floatrect, const float angle) {
    if (floatrect.height < build_cursor_size_red && floatrect.width < build_cursor_size_red) {
        switch (type) {
            case GAME_OBJECT_TYPE::BLOCK: {
                block_list.push_front(Block(floatrect));
                break;
            }
            case GAME_OBJECT_TYPE::SPIKE: {
                spike_list.push_front(Spike(floatrect, angle));
                break;
            }
            case GAME_OBJECT_TYPE::TRAMPLIN: {
                tramplin_list.push_front(Tramplin(floatrect));
                break;
            }
            case GAME_OBJECT_TYPE::SHURIKEN: {
                shuriken_list.push_front(Shuriken(floatrect));
                break;
            }
            case GAME_OBJECT_TYPE::STAIR: {
                stair_list.push_front(Stair(floatrect, angle));
                break;
            }
            case GAME_OBJECT_TYPE::LASER: {
                if (floatrect.height*floatrect.width > 1.0f) {
                    laser_list.push_front(Laser(floatrect, angle));
                }
                break;
            }
            case GAME_OBJECT_TYPE::DOOR: {
                Door door(floatrect, window);
                door_list.insert(std::make_pair(door.getFillColor().toInteger(), std::move(door)));
                break;
            }
            case GAME_OBJECT_TYPE::KEY: {
                Key key(floatrect, window);
                key_list.insert(std::make_pair(key.getFillColor().toInteger(), std::move(key)));
                break;
            }
        }
    }
}

void Game_Objects::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::FloatRect rect = sf::FloatRect(target.getView().getCenter() - target.getView().getSize()/2.0f, target.getView().getSize());
    for (const auto& it : block_list) {
        if (rect.intersects(it.getGlobalBounds())) {
            target.draw(it, states);
        }
    }
    for (const auto& it : spike_list) {
        if (rect.intersects(it.getGlobalBounds())) {
            target.draw(it, states);
        }
    }
    for (const auto& it : tramplin_list) {
        if (rect.intersects(it.getGlobalBounds())) {
            target.draw(it, states);
        }
    }
    for (const auto& it : shuriken_list) {
        if (rect.intersects(it.getGlobalBounds())) {
            target.draw(it, states);
        }
    }
    for (const auto& it : stair_list) {
        if (rect.intersects(it.getGlobalBounds())) {
            target.draw(it, states);
        }
    }
    for (const auto& it : laser_list) {
        if (rect.intersects(it.getGlobalBounds())) {
            target.draw(it, states);
        }
    }
    for (const auto& it : door_list) {
        if (rect.intersects(it.second.getGlobalBounds())) {
            target.draw(it.second, states);
        }
    }
    for (const auto& it : key_list) {
        if (rect.intersects(it.second.getGlobalBounds())) {
            target.draw(it.second, states);
        }
    }
}




}