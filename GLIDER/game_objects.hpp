#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <unordered_map>

namespace krv {

const float build_cursor_size_red = 50.0f; 

enum class GAME_OBJECT_TYPE : int {
    BLOCK,
    SPIKE,
    TRAMPLIN,
    SHURIKEN,
    STAIR,
    LASER,
    DOOR,
    KEY,
    NOTHING,
};

class Block : public sf::RectangleShape {
    sf::Texture texture;

  public:
    Block(const sf::FloatRect &floatrect);

    ~Block() = default;

    Block(const Block& value);

    Block& operator=(const Block& value);

    Block(Block&& value);

    Block& operator=(Block&& value);
};



class Spike : public sf::RectangleShape {
    sf::Texture texture;

  public:
    Spike(const sf::FloatRect &floatrect, const float angle);

    ~Spike() = default;

    Spike(const Spike& value);

    Spike& operator=(const Spike& value);

    Spike(Spike&& value);

    Spike& operator=(Spike&& value);
};



class Tramplin : public sf::RectangleShape {
    sf::Texture texture;

  public:
    Tramplin(const sf::FloatRect &floatrect);

    ~Tramplin() = default;

    Tramplin(const Tramplin& value);

    Tramplin& operator=(const Tramplin& value);

    Tramplin(Tramplin&& value);

    Tramplin& operator=(Tramplin&& value);
};



class Shuriken : public sf::RectangleShape {
    sf::Texture texture;

  public:
    Shuriken(const sf::FloatRect &floatrect);

    ~Shuriken() = default;

    Shuriken(const Shuriken& value);

    Shuriken& operator=(const Shuriken& value);

    Shuriken(Shuriken&& value);

    Shuriken& operator=(Shuriken&& value);
};



class Stair : public sf::RectangleShape {
    bool vertical;
    sf::Texture texture;
  public:
    Stair(const sf::FloatRect &floatrect, const float angle);

    ~Stair() = default;

    Stair(const Stair& value);

    Stair& operator=(const Stair& value);

    Stair(Stair&& value);

    Stair& operator=(Stair&& value);

    bool get_vertical() const;
};



class Laser : public sf::RectangleShape {
    sf::Texture texture;

  public:
    Laser(const sf::FloatRect &floatrect, const float angle);

    ~Laser() = default;

    Laser(const Laser& value);

    Laser& operator=(const Laser& value);

    Laser(Laser&& value);

    Laser& operator=(Laser&& value);
};



class Door : public sf::RectangleShape {
    sf::Texture texture;

  public:
    Door(const sf::FloatRect &floatrect, sf::RenderWindow &window);

    ~Door() = default;

    Door(const Door& value);

    Door& operator=(const Door& value);

    Door(Door&& value);

    Door& operator=(Door&& value);
};



class Key : public sf::RectangleShape {
    sf::Texture texture;

  public:
    Key(const sf::FloatRect &floatrect, sf::RenderWindow &window);

    ~Key() = default;

    Key(const Key& value);

    Key& operator=(const Key& value);

    Key(Key&& value);

    Key& operator=(Key&& value);
};



class Game_Objects : public sf::Drawable {
    std::list<Block> block_list;
    std::list<Spike> spike_list;
    std::list<Tramplin> tramplin_list;
    std::list<Shuriken> shuriken_list;
    std::list<Stair> stair_list;
    std::list<Laser> laser_list;
    std::unordered_multimap<int, Door> door_list;
    std::unordered_multimap<int, Key> key_list;


  public:
    void add(sf::RenderWindow &window, GAME_OBJECT_TYPE type, const sf::FloatRect &floatrect, const float angle);

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};




}