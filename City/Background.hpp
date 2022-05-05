#ifndef CITY_BACKGROUND_HPP
#define CITY_BACKGROUND_HPP


#include <SFML/Graphics.hpp>

using namespace sf;

class Background {
    Texture texture;
public:
    RectangleShape sprite;

    Background(float x, float y, std::string string);

    Background(RenderWindow const &window, std::string string);
};


#endif //CITY_BACKGROUND_HPP
