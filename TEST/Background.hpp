#ifndef TEST_BACKGROUND_HPP
#define TEST_BACKGROUND_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Background {
  Texture texture;
public:
  RectangleShape sprite;

  Background(float x, float y, std::string string);

  Background(RenderWindow const &window, std::string string);
};

#endif //TEST_BACKGROUND_HPP
