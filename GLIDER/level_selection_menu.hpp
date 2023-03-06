#pragma once

#include <SFML/Graphics.hpp>

namespace krv {

enum class LEVEL_SELECTION_TYPE {
    BUILD,
    PLAY,
};

void level_selection_menu(sf::RenderWindow &window, LEVEL_SELECTION_TYPE level_selection_menu);

}