#include "Tile.hpp"

int number_of_tile_types() {
  return static_cast<int>(Tile_Type::NONE) + 1;
}

void Tile::TileBegin() {
  sprite.setSize(Vector2f(80.0f, 15.0f));
  sprite.setOrigin(sprite.getSize()/2.0f);
  speed_generator();
}

void Tile::set_pos(float x, float y) {
  sprite.setPosition(Vector2f(x, y));
}

Tile::Tile() {
  TileBegin();
  texture.loadFromFile("../pic/tiles.png");
  sprite.setTexture(&texture);
}

void Tile::TileSet(float x, float y, Tile_Type tile_type) {
  type = tile_type;
  set_pos(x, y);
  sprite.setTextureRect(IntRect( 0, static_cast<int>(tile_type)*static_cast<int>(sprite.getSize().y), static_cast<int>(sprite.getSize().x), static_cast<int>(sprite.getSize().y) ));
}

void Tile::speed_generator() {
  float var = static_cast<float>(rand()%100);
  if (var < 60.0f) {speed = 0.0f; return;}
  var = var - 30.0f;
  speed = var*5.0f;
}

Tile_Type Tile::get_type() {
  return type;
}

Vector2f Tile::get_pos() {
  return sprite.getPosition();
}

float Tile::get_speed() {
  return speed;
}

void Tile::change_speed() {
  speed = -speed;
}