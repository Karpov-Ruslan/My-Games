#ifndef CITY_BUTTON_HPP
#define CITY_BUTTON_HPP


#include <SFML/Graphics.hpp>

using namespace sf;

class Button {

    Texture texture;
public:
    RectangleShape sprite;

    Button(float pos_x, float pos_y, float delta_x, float delta_y, std::string string);

    bool point_on(float x, float y);

    bool smth_pressed_on(float x, float y, Event &event);


};


#endif //CITY_BUTTON_HPP
