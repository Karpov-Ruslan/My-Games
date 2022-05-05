#include "Column.hpp"

Column::Column() {
    texture.loadFromFile("../pic/column.png");
    upper.setTexture(&texture);
    lower.setTexture(&texture);
}

void Column::ColumnCtr(float x, float y) {
    upper.setPosition(x, y);
    upper.setSize(Vector2f(column_width, -800.0f));
    lower.setPosition(x, y + gap_length);
    lower.setSize(Vector2f(column_width, 800.0f));
}

void Column::column_game_cycle(float horizontal_delta) {
    upper.move(-horizontal_delta, 0.0f);
    lower.move(-horizontal_delta, 0.0f);
    if (upper.getGlobalBounds().left + upper.getGlobalBounds().width < 0.0f) {
        upper.move(5*lenght_beetwin_columns, 0.0f);
        float y = rand()%(600 - (int)gap_length) + 100;
        upper.setPosition(upper.getPosition().x, y);
        lower.move(5*lenght_beetwin_columns, 0.0f);
        lower.setPosition(lower.getPosition().x, y + gap_length);
    }
}