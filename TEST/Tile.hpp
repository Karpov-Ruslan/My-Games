#ifndef TEST_TILE_HPP
#define TEST_TILE_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

const int score_between_events = 500;
const int score_length_events = 100;
const float const_delta_between_tiles = 100.0f;
const float rand_delta_between_tiles = 200.0f;
const float height_first_tile = 600.0f;

enum class Tile_Type : int {
  SIMPLE,
  JUMP,
  ROOF,
  HIDER,
  TELEPORT,
  NONE,
};

int number_of_tile_types();


class Tile{
private:
  Tile_Type type;
  float speed;
  Texture texture;
public:
  RectangleShape sprite;

private:

  void TileBegin();

  void set_pos(float x, float y);

public:
  Tile();

  void TileSet(float x, float y, Tile_Type tile_type = Tile_Type::SIMPLE);

  void speed_generator();

  Tile_Type get_type();

  Vector2f get_pos();

  float get_speed();

  void change_speed();

};

#endif //TEST_TILE_HPP
