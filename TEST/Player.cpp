#include "Player.hpp"

void Player::player_best_score_read() {
  std::ifstream fout("./best_score.bin");
  if(fout.is_open()) {
    std::string string_of_best_score;
    fout >> string_of_best_score;
    best_score = std::stof(string_of_best_score);
    fout.close();
  }
  else {
    best_score = 0.0f;
  }
}

void Player::player_best_score_recording() {
  std::ofstream fin("./best_score.bin");
  fin << std::to_string(static_cast<long long>(best_score));
  fin.close();
}

 void Player::player_best_score_recording(float write_number) {
  std::ofstream fin("./best_score.bin");
  fin << std::to_string(static_cast<long long>(write_number));
  fin.close();
}

Player::Player(float x, float y, float speed) : speed(speed), score(0.0f) {
  sprite.setSize(Vector2f(50.0f, 50.0f));
  sprite.setOrigin(Vector2f(sprite.getSize().x / 2.0f, sprite.getSize().y));
  sprite.setPosition(Vector2f(x, y));
  static Texture player_texture;
  player_texture.loadFromFile("../pic/player.png");
  sprite.setTexture(&player_texture);
  player_best_score_read();
}

Player::~Player() {
  player_best_score_recording();
}