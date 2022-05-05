#ifndef CITY_COLUMN_HPP
#define CITY_COLUMN_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

const float column_width = 80.0f;
const float lenght_beetwin_columns = 250.0f;
const float gap_length = 250.0f;

class Column {
    Texture texture;
public:
    RectangleShape upper;
    RectangleShape lower;

    Column();

    void ColumnCtr(float x, float y);

    void column_game_cycle(float horizontal_delta);
};


#endif //CITY_COLUMN_HPP
