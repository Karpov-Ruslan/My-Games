#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <unordered_map>
#include "player.hpp"
#include "level_selection_menu.hpp"

namespace krv {

const float build_cursor_size_red = 50.0f; 

enum class GAME_OBJECT_TYPE : int {
    BLOCK,
    SPIKE,
    TRAMPLIN,
    SHURIKEN, //Update with time
    STAIR,
    LASER, //Update with time
    DOOR,
    KEY,
    FINISH,
    BACKGROUND,
    NOTHING,
};

class Sky : public sf::Drawable {
    sf::Texture sky_texture;
    sf::RectangleShape sky;
    sf::Texture clouds_texture;
    sf::RectangleShape clouds;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  public:
    Sky(const sf::RenderWindow &window);

    void update(const float d_time);

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

    static void player_collision(Player &player, const std::list<Block> &list);
};



class Spike : public sf::RectangleShape {
    float angle;
    sf::Texture texture;

  public:
    Spike(const sf::FloatRect &floatrect, const float angle);

    ~Spike() = default;

    Spike(const Spike& value);

    Spike& operator=(const Spike& value);

    Spike(Spike&& value);

    Spike& operator=(Spike&& value);

    float get_angle() const;

    static void player_collision(Player &player, const std::list<Spike> &list);
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

    static void player_collision(Player &player, const std::list<Tramplin> &list);
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

    void update(const float d_time);

    static void player_collision(Player &player, std::list<Shuriken> &list, const float d_time);
};



class Stair : public sf::RectangleShape {
    float angle;
    sf::Texture texture;
  public:
    Stair(const sf::FloatRect &floatrect, const float angle);

    ~Stair() = default;

    Stair(const Stair& value);

    Stair& operator=(const Stair& value);

    Stair(Stair&& value);

    Stair& operator=(Stair&& value);

    float get_angle() const;

    static void player_collision(Player &player, const std::list<Stair> &list);
};



class Laser : public sf::RectangleShape {
    float angle;
    sf::Texture texture;
    static sf::Shader shader;
    bool is_work = true;

    ///////////////////////////////////
    //______             _______________
    //      |           |               |
    //      |           |               |
    //      |___________|               |______
    //<(-t0)> <-t_down--> <----t_up----->
    ///////////////////////////////////
    enum class TIME_TYPE {
        T_DOWN,
        T_UP,
        T0,
    };
    
    float t_down = 1.0f;
    float t_up = 1.0f;
    float t0 = 0.0f;


    bool set_times(sf::RenderWindow &window, TIME_TYPE time_type);

  public:
    std::list<sf::Text>::iterator text_it;

    std::string get_times() const;
    
    Laser(const sf::FloatRect &floatrect, const float angle, sf::RenderWindow &window);

    Laser(const sf::FloatRect &floatrect, const float angle, float T_down, float T_up, float T_0);

    ~Laser() = default;

    Laser(const Laser& value);

    Laser& operator=(const Laser& value);

    Laser(Laser&& value);

    Laser& operator=(Laser&& value);

    float get_angle() const;

    static void set_shader();

    void update(const float d_time);

    static void player_collision(Player &player, std::list<Laser> &list, const float d_time);

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



class Door : public sf::RectangleShape {
    sf::Texture texture;

  public:
    Door(const sf::FloatRect &floatrect, sf::RenderWindow &window);

    Door(const sf::FloatRect &floatrect, const sf::Color &color);

    ~Door() = default;

    Door(const Door& value);

    Door& operator=(const Door& value);

    Door(Door&& value);

    Door& operator=(Door&& value);

    static void player_collision(Player &player, const std::unordered_multimap<int, Door> &list);
};



class Key : public sf::RectangleShape {
    sf::Texture texture;

  public:
    Key(const sf::FloatRect &floatrect, sf::RenderWindow &window);

    Key(const sf::FloatRect &floatrect, const sf::Color &color);

    ~Key() = default;

    Key(const Key& value);

    Key& operator=(const Key& value);

    Key(Key&& value);

    Key& operator=(Key&& value);

    static void player_collision(Player &player, std::unordered_multimap<int, Door> &door_list, std::unordered_multimap<int, Key> &key_list);
};



class Finish : public sf::RectangleShape {
    sf::Texture texture;

  public:
    Finish() = default;

    Finish(const sf::FloatRect &floatrect);

    ~Finish() = default;

    Finish(const Finish& value);

    Finish& operator=(const Finish& value);

    Finish(Finish&& value);

    Finish& operator=(Finish&& value);

    void player_collision(Player &player);
};



class Background : public sf::RectangleShape {
    sf::Texture texture;

  public:
    Background(const sf::FloatRect &floatrect);

    ~Background() = default;

    Background(const Background& value);

    Background& operator=(const Background& value);

    Background(Background&& value);

    Background& operator=(Background&& value);

};



class Game_Objects : public sf::Drawable {
    LEVEL_SELECTION_TYPE level_selection_type;
    sf::Font arial;

    //Collision with background
    std::list<Block> block_list;
    std::list<Tramplin> tramplin_list;
    std::list<Background> background_list;
    std::unordered_multimap<int, Door> door_list;
    //No collision with background
    std::list<Spike> spike_list;
    std::list<Shuriken> shuriken_list;
    std::list<Stair> stair_list;
    std::list<Laser> laser_list;
    std::unordered_multimap<int, Key> key_list;
    Finish finish;

    std::list<sf::Text> laser_disription_list;
    Player player;
    //Static
    Sky sky;
    

    bool intersects(const sf::FloatRect &floatrect) const;

    bool intersects_for_background(const sf::FloatRect &floatrect) const;

    void load(const std::string &level_name);

  public:
    void player_jump();

    void save(const std::string &level_name) const;

    void update(const float d_time);

    Game_Objects(const sf::RenderWindow &window, LEVEL_SELECTION_TYPE level_selection_type, const std::string &level_name);

    void add(sf::RenderWindow &window, GAME_OBJECT_TYPE type, const sf::FloatRect &floatrect, const float angle);

    void remove(const sf::FloatRect &floatrect);

    sf::FloatRect remove_shading(const sf::FloatRect &floatrect) const;

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};




}