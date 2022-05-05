#ifndef TEST_PLAYER_HPP
#define TEST_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <fstream>

using namespace sf;

const float G = 3200.0f;
const float horizontal_V = 500.0f;
const float push_vertical_V = 1600.0f;
const float max_height = 350.0f;

class Player {

public:
  RectangleShape sprite;
  float speed;
  float score;
  float best_score;

  void player_best_score_read();

  void player_best_score_recording();

  static void player_best_score_recording(float write_number);

  Player(float x = 240.0f, float y = 900.f, float speed = push_vertical_V);

  ~Player();

};

#endif //TEST_PLAYER_HPP
