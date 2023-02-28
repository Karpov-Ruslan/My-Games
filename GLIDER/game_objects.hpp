#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "player.hpp"

namespace krv {

const int factor = 50;

enum class GAME_OBJECT_TYPE : int {
    BLOCK,
    NOTHING,
};

// class Game_Object : public sf::Drawable {
//   public:
//     Game_Object() {};

//     virtual void player_reaction(Player &player) {

//     }

//     virtual void update(float time) {

//     }
//   private:
//     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
//         std::cout << "Ruslan gay" << std::endl;
//     };

// };

class Block : public sf::RectangleShape {
    sf::Texture texture;

  public:
    Block(const sf::FloatRect &floatrect) : sf::RectangleShape() {
        setPosition(floatrect.left, floatrect.top);
        setSize(sf::Vector2f(floatrect.width, floatrect.height));

        sf::RenderTexture render_texture;
        int x = static_cast<int>(floatrect.width);
        int y = static_cast<int>(floatrect.height);
        render_texture.create(factor*x, factor*y);
        render_texture.clear();
        sf::RectangleShape shape(sf::Vector2f(factor, factor));
        sf::Texture buffer;
        buffer.loadFromFile("../pic/Glider/game_objects.png");
        shape.setTexture(&buffer);
        shape.setTextureRect(sf::IntRect(0, 0, factor, factor));
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                shape.setPosition(factor*i, factor*j);
                render_texture.draw(shape);
            }
        }
        render_texture.display();
        texture = render_texture.getTexture();
        setTexture(&texture);
    }

    ~Block() = default;

    Block(const Block& block) : sf::RectangleShape(block) {
        texture = block.texture;
        setTexture(&texture);
    }

    Block& operator=(const Block& block) {
        (*this).sf::RectangleShape::operator=(block);
        texture = block.texture;
        setTexture(&texture);
        return  *this;
    }

    Block(Block&& block) : sf::RectangleShape(block) {
        texture = block.texture;
        setTexture(&texture);
    }

    Block& operator=(Block&& block) {
        (*this).sf::RectangleShape::operator=(block);
        texture = block.texture;
        setTexture(&texture);
        return  *this;
    }
};





class Game_Objects : public sf::Drawable {
    std::list<Block> block_list;

  public:
    void add(GAME_OBJECT_TYPE type, const sf::FloatRect &floatrect) {
        switch (type) {
            case GAME_OBJECT_TYPE::BLOCK: {
                block_list.push_front(Block(floatrect));
                break;
            }
        }
    }

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (auto it : block_list) {
            target.draw(it, states);
        }
    }
};




}